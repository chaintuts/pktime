/* This file contains the underlying implementation for BitAddr functions
*
* Author: Josh McIntyre
*/

#include <string.h>
#include <sha2.h>
#include <ripemd160.h>
#include <secp256k1.h>
#include <ecdsa.h>
#include <rand.h>
#include <base58.h>
#include <stdio.h>

// Some size definitions we'll need to implement the pubkey -> address conversion
size_t RAW_ADDRESS_NOCHECK_LENGTH = 21;
size_t RAW_ADDRESS_CHECK_LENGTH = 25;
size_t PUBKEY_65_LENGTH = 65;
size_t CHECKSUM_LENGTH = 4;
size_t ADDRESS_LENGTH = 40;
size_t RAW_PRIVKEY_NOCHECK_LENGTH = 33;
size_t RAW_PRIVKEY_CHECK_LENGTH = 37;
size_t PRIVKEY_WIF_LENGTH = 70;

unsigned char BTC_ADDR_PREFIX = 0x0;
unsigned char BTC_WIF_PREFIX = 0x80;

// Calculate the secp256k1 public key from the private key
void pubkey_from_privkey(unsigned char privkey[SHA256_DIGEST_LENGTH],  unsigned char pubkey[PUBKEY_65_LENGTH])
{
	 ecdsa_get_public_key65(&secp256k1, (uint8_t*) privkey,
                            (uint8_t*) pubkey);
}

// Generate address from pubkey
void address_from_pubkey(const unsigned char pubkey[PUBKEY_65_LENGTH], unsigned char version_prefix, unsigned char address[ADDRESS_LENGTH])
{
	// First, "double hash" the public key
	unsigned char round_1[SHA256_DIGEST_LENGTH];
	unsigned char round_2[RIPEMD160_DIGEST_LENGTH];

	sha256_Raw((uint8_t*) pubkey, PUBKEY_65_LENGTH, (uint8_t*) round_1);
	ripemd160((uint8_t*) round_1, SHA256_DIGEST_LENGTH, (uint8_t*) round_2);

	// Add the version specifier
	unsigned char raw_address_nocheck[RAW_ADDRESS_NOCHECK_LENGTH];
	raw_address_nocheck[0] = version_prefix;
	memcpy(raw_address_nocheck + 1, round_2, RIPEMD160_DIGEST_LENGTH);

	// Generate a checksum
	unsigned char check_round_1[SHA256_DIGEST_LENGTH];
	unsigned char check_round_2[SHA256_DIGEST_LENGTH];
	unsigned char checksum[CHECKSUM_LENGTH];

	sha256_Raw((uint8_t*) raw_address_nocheck, RAW_ADDRESS_NOCHECK_LENGTH, check_round_1);
	sha256_Raw((uint8_t*) check_round_1, SHA256_DIGEST_LENGTH, check_round_2);
	memcpy(checksum, check_round_2, CHECKSUM_LENGTH);


	// Finalize the raw address
	// 1 byte for the version string
	// 20 bytes for the pubkey hash
	// 4 bytes for the checksum
	unsigned char raw_address_check[RAW_ADDRESS_CHECK_LENGTH];
	memcpy(raw_address_check, raw_address_nocheck, RAW_ADDRESS_NOCHECK_LENGTH);
	memcpy(raw_address_check + RAW_ADDRESS_NOCHECK_LENGTH, checksum, CHECKSUM_LENGTH);

	// Base58 encode
	b58enc((char*) address, &ADDRESS_LENGTH, raw_address_check, RAW_ADDRESS_CHECK_LENGTH);
}

void privkey_wif_from_raw(unsigned char* privkey_raw, unsigned char version_prefix, unsigned char* privkey)
{
	
	// Add the version specifierd
	unsigned char raw_privkey_nocheck[RAW_PRIVKEY_NOCHECK_LENGTH];
	raw_privkey_nocheck[0] = version_prefix;
	memcpy(raw_privkey_nocheck + 1, privkey_raw, SHA256_DIGEST_LENGTH);

	// Generate a checksum
	unsigned char check_round_1[SHA256_DIGEST_LENGTH];
	unsigned char check_round_2[SHA256_DIGEST_LENGTH];
	unsigned char checksum[CHECKSUM_LENGTH];

	sha256_Raw((uint8_t*) raw_privkey_nocheck, RAW_PRIVKEY_NOCHECK_LENGTH, check_round_1);
	sha256_Raw((uint8_t*) check_round_1, SHA256_DIGEST_LENGTH, check_round_2);
	memcpy(checksum, check_round_2, CHECKSUM_LENGTH);


	// Finalize the raw WIF format privkey
	// 1 byte for the version string - 0x80 for mainneti BTC/BCH
	// 32 bytes for the raw private key data
	// 4 bytes for the checksum
	unsigned char raw_privkey_check[RAW_PRIVKEY_CHECK_LENGTH];
	memcpy(raw_privkey_check, raw_privkey_nocheck, RAW_PRIVKEY_NOCHECK_LENGTH);
	memcpy(raw_privkey_check + RAW_PRIVKEY_NOCHECK_LENGTH, checksum, CHECKSUM_LENGTH);

	// Base58 encode
	b58enc((char*) privkey, &PRIVKEY_WIF_LENGTH, raw_privkey_check, RAW_PRIVKEY_CHECK_LENGTH);
}

// Go through the real steps to generate a Bitcoin keypair
void generate_bitcoin_keypair()
{
	// Use a predefined privkey - we're just using this function to estimate
	// the time it takes to generate a keypair on this system
	// Then generate the public key from the private key
	unsigned char privkey_raw[SHA256_DIGEST_LENGTH] = { 0x0 };
	unsigned char pubkey[PUBKEY_65_LENGTH];
	pubkey_from_privkey(privkey_raw, pubkey);

	// Generate the address from the public key
	// This address can use the legacy base58check encoding valid
	// in both BTC and BCH, or BCH cashaddr
	unsigned char address[ADDRESS_LENGTH];
	address_from_pubkey(pubkey, BTC_ADDR_PREFIX, address);
}

