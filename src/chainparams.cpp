// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2017 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <chainparams.h>
#include <consensus/merkle.h>

#include <tinyformat.h>
#include <util.h>
#include <utilstrencodings.h>
#include <arith_uint256.h>
#include <versionbits.h>

#include <assert.h>

#include <chainparamsseeds.h>

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 504365040 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(MakeTransactionRef(std::move(txNew)));
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

/**
 * Build the genesis block. Note that the output of its generation
 * transaction cannot be spent since it did not originally exist in the
 * database.
 *
 * CBlock(hash=0x0000018d2d31e4ed7df7b699d32cc1f4da1ba6e3e6f49a2b33b9ff43ffa630e0,
 *        ver=0x20000000,
 *        hashPrevBlock=0x0000000000000000000000000000000000000000000000000000000000000000,
 *        hashMerkleRoot=0x5fd8818c00a3e171e4d43e7194dfbc8df60ded3416e79af1688b3e5448c8564a,
 *        nTime=1509526800,
 *        nBits=1e0f901d,
 *        nNonce=7240431,
 *        vtx=1)
 * CTransaction(hash=824c6bf009, ver=1, vin.size=1, vout.size=1, nLockTime=0)
 *  CTxIn(COutPoint(0000000000, 4294967295), coinbase 00046931fc5923444a49412033312f4e6f762f3230313720636c6f7365642061742032333337372e3234)
 *  CScriptWitness()
 *  CTxOut(nValue=50.00000000, scriptPubKey=048183aecd19078802388a000d81b)
 */
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "DJIA 31/Nov/2017 closed at 23377.24";
    const CScript genesisOutputScript = CScript() << ParseHex("044c761271482fb8245dfc2a73fe461cffb6e054aa2c8f76f97fc76b49f0a6a3ed0339689e02a5129608eb14cdb0674e9d5200077309bcbcf18bbd7a6eee16e356") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

void CChainParams::UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    consensus.vDeployments[d].nStartTime = nStartTime;
    consensus.vDeployments[d].nTimeout = nTimeout;
}

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */
class CMainParams : public CChainParams {
public:
    static const uint256 HASH_GENESIS    = uint256S("0x0000018d2d31e4ed7df7b699d32cc1f4da1ba6e3e6f49a2b33b9ff43ffa630e0");
    static const uint256 HASH_MERKLEROOT = uint256S("0x5fd8818c00a3e171e4d43e7194dfbc8df60ded3416e79af1688b3e5448c8564a");
public:
    CMainParams() {
        strNetworkID = "main";
        consensus.nSubsidyHalvingInterval = 840000;
        consensus.BIP16Height = 0;
        consensus.BIP34Height = 0;
        consensus.BIP34Hash = HASH_GENESIS;
        consensus.BIP65Height = 0;
        consensus.BIP66Height = 0;

        consensus.powLimit = uint256S("0x00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 14 * 24 * 60 * 60; // two weeks
        consensus.nPowTargetSpacing = 10 * 60;
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;

        consensus.nRuleChangeActivationThreshold = 1916; // 95% of 2016
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing

        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0; // January 1, 1970
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1527782400; // Jun. 1, 2018

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 0; // January 1, 1970
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1527782400; // Jun. 1, 2018

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 0; // January 1, 1970
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1527782400; // Jun. 1, 2018

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00000000000000000000000000000000000000000000000000000000000fffff");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid.SetNull();

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         * 0x901dcafe => goldcafe
         */
        pchMessageStart[0] = 0x90;
        pchMessageStart[1] = 0x1d;
        pchMessageStart[2] = 0xca;
        pchMessageStart[3] = 0xfe;
        nDefaultPort = 30333;
        nPruneAfterHeight = 104832; // about 2 years

        genesis = CreateGenesisBlock(1509526800            /*20171101-170000*/
                                     , 7240431             /*nonce*/
                                     , 0x1e0ffff0          /*bits*/
                                     , VERSIONBITS_TOP_BITS/*version*/
                                     , 50 * COIN           /*subsidy*/);

        assert(genesis.GetHash() == HASH_GENESIS);
        assert(genesis.hashMerkleRoot == HASH_MERKLEROOT);
        consensus.hashGenesisBlock = genesis.GetHash();

        // Ref: https://en.bitcoin.it/wiki/List_of_address_prefixes
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,38); // 'G'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,63); // 'S'
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,128);// '5' for uncompressed, 'K','L' for compressed
        // BIP32 pubkey
        base58Prefixes[EXT_PUBLIC_KEY] = {4, 136, 178, 30}; // xpub
        // BIP32 private key
        base58Prefixes[EXT_SECRET_KEY] = {4, 136, 173, 228};// xprv

        bech32_hrp = "BTG";

        // Note that of those with the service bits flag, most only support a subset of possible options
        vSeeds.emplace_back("seed.bitgold.bitbaba.com", false);

        //vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;

        checkpointData = {
            {
                {     0, HASH_GENESIS},
            }
        };

        basepointData = {
            {
                {     0, HASH_GENESIS},
            }
        };

        chainTxData = ChainTxData{
            1509526606, // * UNIX timestamp of last known number of transactions, here 20171101-165646
            1,          // * total number of transactions between genesis and that timestamp
                        //   (the tx=... number in the SetBestChain debug.log lines)
            3.5         // * estimated number of transactions per second after that timestamp
        };
    }
};

/**
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams {
public:
    static const uint256 HASH_GENESIS    = uint256S("0x54192846adbe9997460098a0fd4f041c7456429d6885adc0c7d4900f04621b8b");
    static const uint256 HASH_MERKLEROOT = uint256S("0x5fd8818c00a3e171e4d43e7194dfbc8df60ded3416e79af1688b3e5448c8564a");
public:
    CTestNetParams() {
        strNetworkID = "test";
        consensus.nSubsidyHalvingInterval = 840000;
        consensus.BIP16Height = 0;
        consensus.BIP34Height = 0;
        consensus.BIP34Hash = HASH_GENESIS;
        consensus.BIP65Height = 0;
        consensus.BIP66Height = 0;
        consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 14 * 24 * 60 * 60; // two weeks
        consensus.nPowTargetSpacing = 10 * 60;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;

        consensus.nRuleChangeActivationThreshold = 1008; // 50% for testchains
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing

        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0; // January 1, 1970
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1527782400; // Jun. 1, 2018

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 0; // January 1, 1970
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1527782400; // Jun. 1, 2018

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 0; // January 1, 1970
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1527782400; // Jun. 1, 2018

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000000000000000000000001");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = HASH_GENESIS;

        /**
        * 0xc01dbeef => cold beef
        */
        pchMessageStart[0] = 0xc0;
        pchMessageStart[1] = 0x1d;
        pchMessageStart[2] = 0xbe;
        pchMessageStart[3] = 0xef;
        nDefaultPort = 40333;
        nPruneAfterHeight = 104832;

        genesis = CreateGenesisBlock(1509526800             /*20171101-170000*/
                                     , 1                    /*nonce*/
                                     , 0x207fffff           /*bits*/
                                     , VERSIONBITS_TOP_BITS /*version*/
                                     , 50 * COIN            /*subsidy*/);


        assert(genesis.GetHash() == HASH_GENESIS);
        assert(genesis.hashMerkleRoot == HASH_MERKLEROOT);
        consensus.hashGenesisBlock = genesis.GetHash();

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,97); // 'g'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,125);// 's'
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);// '9' for uncompressed, 'c' for compressed
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};// tpub
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};// tprv

        bech32_hrp = "btg";

        //vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;

        checkpointData = {
            {
                {     0, HASH_GENESIS},
            }
        };

        basepointData = {
            {
                {     0, HASH_GENESIS},
            }
        };

        chainTxData = ChainTxData{
            1509526606, // * UNIX timestamp of last known number of transactions, here 20171101-165646
            1,          // * total number of transactions between genesis and that timestamp
                        //   (the tx=... number in the SetBestChain debug.log lines)
            3.1         // * estimated number of transactions per second after that timestamp
        };

    }
};

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    static const uint256 HASH_GENESIS    = uint256S("0x1285c90cd4cbd709bc3db0494f7b2631daa7945aa1311872b5fcba8b7c0352ea");
    static const uint256 HASH_MERKLEROOT = uint256S("0x5fd8818c00a3e171e4d43e7194dfbc8df60ded3416e79af1688b3e5448c8564a");
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        consensus.nSubsidyHalvingInterval = 150;
        consensus.BIP16Height = 0;
        consensus.BIP34Height = 0;
        consensus.BIP34Hash = HASH_GENESIS;
        consensus.BIP65Height = 0;
        consensus.BIP66Height = 0;
        consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 14 * 24 * 60 * 60; // two weeks
        consensus.nPowTargetSpacing = 10 * 60;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;

        consensus.nRuleChangeActivationThreshold = 72; // 50% for testchains
        consensus.nMinerConfirmationWindow = 144; // Faster than normal for regtest (144 instead of 2016)

        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = Consensus::BIP9Deployment::ALWAYS_ACTIVE;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;

        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = Consensus::BIP9Deployment::ALWAYS_ACTIVE;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;

        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = Consensus::BIP9Deployment::ALWAYS_ACTIVE;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000000000000000000000001");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = HASH_GENESIS;

        /**
        * 0xabadfee1 => a bad feel
        */
        pchMessageStart[0] = 0xab;
        pchMessageStart[1] = 0xad;
        pchMessageStart[2] = 0xfe;
        pchMessageStart[3] = 0xe1;
        nDefaultPort = 40444;
        nPruneAfterHeight = 104832;

        genesis = CreateGenesisBlock(1509526800            /*20171101-170000*/
                                     , 2                   /*nonce*/
                                     , 0x207fffff          /*bits*/
                                     , VERSIONBITS_TOP_BITS/*version*/
                                     , 50 * COIN           /*subsidy*/);

        assert(genesis.GetHash() == HASH_GENESIS);
        assert(genesis.hashMerkleRoot == HASH_MERKLEROOT);

        consensus.hashGenesisBlock = genesis.GetHash();

        vFixedSeeds.clear(); //!< Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //!< Regtest mode doesn't have any DNS seeds.

        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;

        checkpointData = {
            {
                {     0, HASH_GENESIS},
            }
        };

        basepointData = {
            {
                {     0, HASH_GENESIS},
            }
        };

        chainTxData = ChainTxData{
            1509526606, // * UNIX timestamp of last known number of transactions, here 20171101-165646
            1,          // * total number of transactions between genesis and that timestamp
                        //   (the tx=... number in the SetBestChain debug.log lines)
            3.1         // * estimated number of transactions per second after that timestamp
        };

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,61); // 'R'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,122);// 'r'
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);// '9' for uncompressed, 'c' for compressed
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};// tpub
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};// tprv

        bech32_hrp = "GTB";
    }
};

static std::unique_ptr<CChainParams> globalChainParams;

const CChainParams &Params() {
    assert(globalChainParams);
    return *globalChainParams;
}

std::unique_ptr<CChainParams> CreateChainParams(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
        return std::unique_ptr<CChainParams>(new CMainParams());
    else if (chain == CBaseChainParams::TESTNET)
        return std::unique_ptr<CChainParams>(new CTestNetParams());
    else if (chain == CBaseChainParams::REGTEST)
        return std::unique_ptr<CChainParams>(new CRegTestParams());
    throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    globalChainParams = CreateChainParams(network);
}

void UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    globalChainParams->UpdateVersionBitsParameters(d, nStartTime, nTimeout);
}
