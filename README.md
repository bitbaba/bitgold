BitGold Project 
=====================================

[![Build Status](https://travis-ci.org/bitbaba/bitgold.svg?branch=master)](https://travis-ci.org/bitbaba/bitgold)

License
-------

BitGold[BGOLD] is released under the terms of the MIT license. 

See [COPYING](COPYING) for more information or see https://opensource.org/licenses/MIT.


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
  
  How to compile a gamble script? (gamble.md)[https://github.com/bitbaba/bitgold/blob/bitgold/doc/gamble.md]
  
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

