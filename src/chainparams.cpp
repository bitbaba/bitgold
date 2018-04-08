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
    CMainParams() {
        strNetworkID = "main";
        const uint256 HASH_GENESIS    = uint256S("0x0000063f1c6458585e8117e505924b49abc2192f2e1e4b2bd41afce197570357");
        const uint256 HASH_MERKLEROOT = uint256S("0xa1820174d76bb7e15e5eaa357907d1a07c1752d39a08346097bfeff28d42ddd8");
        consensus.nSubsidyHalvingInterval = 420000;
        consensus.BIP16Height = 0;
        consensus.BIP34Height = 1;
        consensus.BIP34Hash = uint256S("0x0000019a6504cae19fa5adb0f5f9a9200c9b5ba5aca3f343b197ae623e3224b0");
        consensus.BIP65Height = 0;
        consensus.BIP66Height = 0;

        consensus.powLimit = uint256S("0x00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 14 * 24 * 60 * 60; // two weeks
        consensus.nPowTargetSpacing = 5 * 60;
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;

        consensus.nMinerConfirmationWindow = 4032; // nPowTargetTimespan / nPowTargetSpacing
        consensus.nRuleChangeActivationThreshold = 3832; // ~95% of 4032

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
                                     , 1080298             /*nonce*/
                                     , 0x1e0ffff0          /*bits*/
                                     , VERSIONBITS_TOP_BITS/*version*/
                                     , 50 * COIN           /*subsidy*/);

        while(false){// search genesis
            static FILE * genesis_file = NULL; if (genesis_file == NULL) {genesis_file = fopen("genesis.info", "w");}
            arith_uint256 hash = UintToArith256(genesis.GetHash());
            arith_uint256 target;
            target.SetCompact(0x1e0ffff0);
            if (hash < target){
                if(genesis_file != NULL){
                    fprintf(genesis_file, "nonce: %d\npow:%s\n%merkle:%s\n\n"
                        , genesis.nNonce
                        , hash.ToString().c_str()
                        , genesis.hashMerkleRoot.ToString().c_str());
                    fclose(genesis_file); genesis_file = NULL;
                    exit(0);
                }
            }
            genesis.nNonce++;
        }

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
        vSeeds.emplace_back("seed.bitgold.bitbaba.com"/*, false*/);

        //vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;

        checkpointData = {
            {
                {     0, HASH_GENESIS},
                {  1008, uint256S("0x00000ff673327dcbfbf65f13a594345bafd6804ad08eac1749939d01989a088d")},
                {  2016, uint256S("0x000005f3b3f9ebddaf6be241619701d3db03b18b165b076862039075e8ab0751")},
                {  4032, uint256S("0x00000306e714368fd891f1321fd2bcce806189de9b7801d557da5a4ccbc3965a")},
                {  8064, uint256S("0x000000beee2315d0432228e365dea0c7324ba0e57a00a227dac5b44952204f79")},
                { 10080, uint256S("0x000001debe0a25b2e017412977e694a67fede7bc38102d2206f441e0a422925a")},
                { 12096, uint256S("0x0000006f36a44118ee46ebb313c6684c8a22fbbd626a3802e416983d5486cefe")},
                { 12186, uint256S("0x000000092fcdc8cde04b50adfefa30e856a2058a2c790a51eaf64bdc40f164b8")},
                { 23702, uint256S("0x0000000352824f5ab9ca70d865d259370897a5dc544c283c43f1ad895d6e1e95")},
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

        /* disable fallback fee on mainnet */
        m_fallback_fee_enabled = false;
    }
};

/**
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        const uint256 HASH_GENESIS    = uint256S("0x7638286a10ad14fc065601355f3aeba6c1ec55469fd928f6d2ae58eb4d975e5f");
        const uint256 HASH_MERKLEROOT = uint256S("0xa1820174d76bb7e15e5eaa357907d1a07c1752d39a08346097bfeff28d42ddd8");
        consensus.nSubsidyHalvingInterval = 420000;
        consensus.BIP16Height = 0;
        consensus.BIP34Height = 100000000; // BIP34 has not activated on testnet
        consensus.BIP34Hash = uint256();
        consensus.BIP65Height = 0;
        consensus.BIP66Height = 0;
        consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 14 * 24 * 60 * 60; // two weeks
        consensus.nPowTargetSpacing = 5 * 60;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;

        consensus.nRuleChangeActivationThreshold = 2016; // 50% for testchains
        consensus.nMinerConfirmationWindow = 4032; // nPowTargetTimespan / nPowTargetSpacing

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

        while(false){
            static FILE * genesis_file = NULL; if (genesis_file == NULL) {genesis_file = fopen("genesis.info", "w");}
            arith_uint256 hash = UintToArith256(genesis.GetHash());
            arith_uint256 target;
            target.SetCompact(0x207fffff);
            if (hash < target){
                if (genesis_file != NULL){
                    fprintf(genesis_file, "nonce: %d\npow:%s\n%merkle:%s\n\n"
                        , genesis.nNonce
                        , hash.ToString().c_str()
                        , genesis.hashMerkleRoot.ToString().c_str());
                    fclose(genesis_file); genesis_file = NULL;
                    exit(0);
                }
            }
            genesis.nNonce++;
        }

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

        /* enable fallback fee on testnet */
        m_fallback_fee_enabled = true;
    }
};

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        const uint256 HASH_GENESIS    = uint256S("0x5fcdf13a912cf23445226c4b42ebd9760479979098890757983f1741fb1a79f0");
        const uint256 HASH_MERKLEROOT = uint256S("0xa1820174d76bb7e15e5eaa357907d1a07c1752d39a08346097bfeff28d42ddd8");
        consensus.nSubsidyHalvingInterval = 420000;
        consensus.BIP16Height = 0;
        consensus.BIP34Height = 100000000; // BIP34 has not activated on regtest (far in the future so block v1 are not rejected in tests)
        consensus.BIP34Hash = uint256();
        consensus.BIP65Height = 0;
        consensus.BIP66Height = 0;
        consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 14 * 24 * 60 * 60; // two weeks
        consensus.nPowTargetSpacing = 5 * 60;
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

        while(false){
            static FILE * genesis_file = NULL; if (genesis_file == NULL) {genesis_file = fopen("genesis.info", "w");}
            arith_uint256 hash = UintToArith256(genesis.GetHash());
            arith_uint256 target;
            target.SetCompact(0x207fffff);
            if (hash < target){
                if (genesis_file != NULL){
                    printf("nonce: %d\npow:%s\n%merkle:%s\n\n"
                        , genesis.nNonce
                        , hash.ToString().c_str()
                        , genesis.hashMerkleRoot.ToString().c_str());
                    fclose(genesis_file); genesis_file = NULL;
                    exit(0);
                }
            }
            genesis.nNonce++;
        }

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

        /* enable fallback fee on regtest */
        m_fallback_fee_enabled = true;
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
