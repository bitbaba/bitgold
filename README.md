BitGold Project 
=====================================

[![Build Status](https://travis-ci.org/bitbaba/bitgold.svg?branch=master)](https://travis-ci.org/bitbaba/bitgold)

Downloads
-------------

- [Win32](https://bintray.bitbaba.com/bitgold/bitgold-win32.tar.gz)
- [Ubuntu](https://bintray.bitbaba.com/bitgold/bitgold-ubuntu64.tar.gz)
- [Mac](https://bintray.bitbaba.com/bitgold/bitgold-mac.tar.gz)

Services
----------------

- [Pool](https://pool.bitbaba.com/)

- [Miner](https://github.com/bitbaba/cpuminer)

- [Explorer](https://bitgold.bitbaba.com/)

- [Exchange](https://ex.bitbaba.com/)

License
-------

BitGold[BGOLD] is released under the terms of the MIT license. 
See [COPYING](COPYING) for more information or see https://opensource.org/licenses/MIT.

Features
--------

- 5 minutes per block(half of bitcoin core)
- 2-Mega-bytes serialized block size(2x bitcoin core)
- 42,000,000 coins in PoW stage(2x of bitcoins and half of litecoins)
- Seg-Witness(same as bitcoin core)
- GoldHash as PoW (now same as sha256d of bitcoin core)

Roadmaps
----------------

- Support chainstate retrieving in script stack machine
  - nonceOf(height)
  
  ```c++
	CScript GetScriptForGamble(int height, const std::vector<CPubKey>& keys)
	{
	    CScript script;
	    script << OP_GAMBLESCRIPT; // simple version of semantic OP_EVAL
	    script << CScriptNum(height);
	    script << OP_NONCEOF;
	    script << CScript::EncodeOP_N(2);
	    script << OP_MOD;
	    script << CScript::EncodeOP_N(0);
	    script << OP_NUMEQUAL;
	    script << OP_IF;
	    script << ToByteVector(keys[0]);
	    script << OP_ELSE;
	    script << ToByteVector(keys[1]);
	    script << OP_ENDIF;
	    script << OP_CHECKSIG;
	    return script;
	}
  ```
  
  ```
	>getnewaddress 'gambler1' legacy 
	GKx8fpnm2RW4ebXq66FhAyym6d6DhLNxiF
	
	>getaddressinfo 
	{
  		"address": "GKx8fpnm2RW4ebXq66FhAyym6d6DhLNxiF",
		...
  		"pubkey": "028ae98df9f28ead984f980393e7bfd865d80a5b484300755dbf25870e4f8f1d56",
		...
	}
	
	>getnewaddress 'gambler2' legacy
	GQSyTMjRoUsCaVfuU4KzfgVha3t642V1X5
	
	>getaddressinfo GQSyTMjRoUsCaVfuU4KzfgVha3t642V1X5
	{
  		"address": "GQSyTMjRoUsCaVfuU4KzfgVha3t642V1X5",
		...
  		"pubkey": "028b040ecb3c4d87e91a82e3f3dd3196b53de8fdb840577e7f8556b48d3ac6d7f3",
		...
	}
	
	>getblockcount 
	26428
	
	>creategamble 26500 "[\"028ae98df9f28ead984f980393e7bfd865d80a5b484300755dbf25870e4f8f1d56\", \"028b040ecb3c4d87e91a82e3f3dd3196b53de8fdb840577e7f8556b48d3ac6d7f3\"]"
	{
  		"address": "Sc8FeTEYnLjEL9qVj3Mqz2nWgTEygTV3ds",
  		"redeemScript": "b9028467b75297009c6321028ae98df9f28ead984f980393e7bfd865d80a5b484300755dbf25870e4f8f1d566721028b040ecb3c4d87e91a82e3f3dd3196b53de8fdb840577e7f8556b48d3ac6d7f368ac"
	}
	
	>sendtoaddress Sc8FeTEYnLjEL9qVj3Mqz2nWgTEygTV3ds 1 "" "" false
	55fe01a00ea0ab336b77c0ef8519fe7865f912f128e8e5db6225185dab6fa968
	
	>sendtoaddress Sc8FeTEYnLjEL9qVj3Mqz2nWgTEygTV3ds 1 "" "" false
	d9e4f6f4c82b89df9ecefba343b16cacfa844f2d9c7e4496f22dd5df6a7943be
	
	>getaddressinfo Sc8FeTEYnLjEL9qVj3Mqz2nWgTEygTV3ds
	{
	  "address": "Sc8FeTEYnLjEL9qVj3Mqz2nWgTEygTV3ds",
	  "scriptPubKey": "a914a2b1ed20c88a9f197b7009053a6ecba9807d8ed787",
	  "ismine": false,
	  "iswatchonly": false,
	  "isscript": true,
	  "iswitness": false
	}
	
	# set a redeem address for winner
	>getnewaddress "winner" legacy
	GYMHC1iRhtKsK2GMAEvybkbSeNTtHakScP
	
	# Redeem from "txid=d9e4f6f4c82b89df9ecefba343b16cacfa844f2d9c7e4496f22dd5df6a7943be,vout=0"
	# and same as "txid=55fe01a00ea0ab336b77c0ef8519fe7865f912f128e8e5db6225185dab6fa968,vout=0"	
	>createrawtransaction "[{\"txid\":\"55fe01a00ea0ab336b77c0ef8519fe7865f912f128e8e5db6225185dab6fa968\", \"vout\":0},{\"txid\":\"d9e4f6f4c82b89df9ecefba343b16cacfa844f2d9c7e4496f22dd5df6a7943be\", \"vout\":0}]" "{\"GYMHC1iRhtKsK2GMAEvybkbSeNTtHakScP\":1.99}"
	020000000268a96fab5d182562dbe5e828f112f96578fe1985efc0776b33aba00ea001fe550000000000ffffffffbe43796adfd52df296447e9c2d4f84faac6cb143a3fbce9edf892bc8f4f6e4d90000000000ffffffff01c07fdc0b000000001976a9149f1f2a4013414b22dfb9aafd0e354fd83e45ec1888ac00000000


  ```
  - hashOf(height)
  - timeOf(height)

- Support PoS (Proof-of-Stake)

- Support state storage of non-utxo data

Mining 
-------------------
- Pool

```
./minerd --algo=sha256d \
         --threads=1 \
         --url=stratum+tcp://pool.bitbaba.com:3333 \
         --no-getwork \
         --no-gbt \
         --user=GZmKHp12bDUiDCkvvzyZzytwRcNaW3viDM \
         --pass=x \
         --debug \
         --protocol-dump
```

- GBT(GetBlockTemplate) on remote rpc

```
./minerd --algo=sha256d \
	 --threads=1 \
	 --coinbase-sig="bitbaba" \
	 --coinbase-addr=GZmKHp12bDUiDCkvvzyZzytwRcNaW3viDM \
	 --url=http://api.bitbaba.com/ \
	 --no-getwork \
	 --user=rpcuser \
	 --pass=rpcpassword \
	 --debug \
	 --protocol-dump
```

- Solo-Mining Locally

```
while true; 
    do ./bitgold-cli generatetoaddress 1 GZmKHp12bDUiDCkvvzyZzytwRcNaW3viDM 10000000; 
done
```

What is BitGold?
----------------

BitGold [BGOLD] is an new digital gold that enables instant payments to
anyone, anywhere in the world. BitGold uses peer-to-peer technology to operate
with no central authority: managing transactions and issuing money are carried
out collectively by the network. BitGold Core is the name of open source
software which enables the use of this currency. 
see [Features](https://github.com/bitbaba/bitgold/blob/master/README.md#features)
and [RoadMaps](https://github.com/bitbaba/bitgold/blob/master/README.md#roadmaps).

For more information, as well as an immediately useable, binary version of
the BitGold Core software, see https://bintray.bitbaba.com/bintray/bitgold, or read the
[bitgold design](http://blog.csdn.net/hacode/article/details/78369398) and
[bitcoin original whitepaper](https://bitcoincore.org/bitcoin.pdf).

Building
------------------

As you known, the .travis.yml is used for automated building. 
Here is a localized script called *travis.sh*, which can be used 
to build bitgold on your local laptop.

Example Usage:

```
$>mkdir -p ~/home/user1/tarballs; \
$>ln -s ~/home/user1/tarballs depends/sources; \
$>mkdir -p depends/sdk-sources depends/SDKs; \
$>sudo apt-get update; \
$>sh travis.sh;
```

>Note: *~/home/user1/tarballs* is used to cache locale source tarballs of depends.

