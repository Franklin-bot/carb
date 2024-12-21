#ifndef BOTAN_BUILD_CONFIG_H_
#define BOTAN_BUILD_CONFIG_H_

/**
* @file  build.h
* @brief Build configuration for Botan 3.6.1
*
* Automatically generated from
* 'configure.py --prefix=/Users/FranklinZhao/carb/lib/botan'
*
* Target
*  - Compiler: clang++ -fstack-protector -m64 -pthread -stdlib=libc++ -std=c++20 -D_REENTRANT -O3
*  - Arch: x86_64
*  - OS: macos
*/

/**
 * @defgroup buildinfo Build Information
 */

/**
 * @ingroup buildinfo
 * @defgroup buildinfo_version Build version information
 * @{
 */

/// The major version of the release
#define BOTAN_VERSION_MAJOR 3
/// The minor version of the release
#define BOTAN_VERSION_MINOR 6
/// The patch version of the release
#define BOTAN_VERSION_PATCH 1

/**
 * Expands to an integer of the form YYYYMMDD if this is an official
 * release, or 0 otherwise. For instance, 2.19.0, which was released
 * on January 19, 2022, has a `BOTAN_VERSION_DATESTAMP` of 20220119.
 */
#define BOTAN_VERSION_DATESTAMP 20241026


#define BOTAN_VERSION_RELEASE_TYPE "release"

/**
 * A macro expanding to a string that is set to a revision identifier
 * corresponding to the source, or "unknown" if this could not be
 * determined. It is set for all official releases, and for builds that
 * originated from within a git checkout.
 */
#define BOTAN_VERSION_VC_REVISION "git:d1ad41eef0d7039f79ac89d180f0d697936b09f1"

/**
 * A macro expanding to a string that is set at build time using the
 * `--distribution-info` option. It allows a packager of the library
 * to specify any distribution-specific patches. If no value is given
 * at build time, the value is the string "unspecified".
 */
#define BOTAN_DISTRIBUTION_INFO "unspecified"

/**
 * @}
 */

/**
 * @ingroup buildinfo
 * @defgroup buildinfo_configuration Build configurations
 * @{
 */

/** How many bits per limb in a BigInt */
#define BOTAN_MP_WORD_BITS 64




#define BOTAN_INSTALL_PREFIX R"(/Users/FranklinZhao/carb/lib/botan)"
#define BOTAN_INSTALL_HEADER_DIR R"(include/botan-3)"
#define BOTAN_INSTALL_LIB_DIR R"(/Users/FranklinZhao/carb/lib/botan/lib)"
#define BOTAN_LIB_LINK "-ldl -framework CoreFoundation -framework Security"
#define BOTAN_LINK_FLAGS "-fstack-protector -m64 -pthread -stdlib=libc++"

#define BOTAN_SYSTEM_CERT_BUNDLE "/etc/ssl/cert.pem"

#ifndef BOTAN_DLL
  #define BOTAN_DLL __attribute__((visibility("default")))
#endif

/* Target identification and feature test macros */

#define BOTAN_TARGET_OS_IS_MACOS

#define BOTAN_TARGET_OS_HAS_APPLE_KEYCHAIN
#define BOTAN_TARGET_OS_HAS_ARC4RANDOM
#define BOTAN_TARGET_OS_HAS_ATOMICS
#define BOTAN_TARGET_OS_HAS_CCRANDOM
#define BOTAN_TARGET_OS_HAS_CLOCK_GETTIME
#define BOTAN_TARGET_OS_HAS_COMMONCRYPTO
#define BOTAN_TARGET_OS_HAS_DEV_RANDOM
#define BOTAN_TARGET_OS_HAS_FILESYSTEM
#define BOTAN_TARGET_OS_HAS_GETENTROPY
#define BOTAN_TARGET_OS_HAS_POSIX1
#define BOTAN_TARGET_OS_HAS_POSIX_MLOCK
#define BOTAN_TARGET_OS_HAS_SANDBOX_PROC
#define BOTAN_TARGET_OS_HAS_SOCKETS
#define BOTAN_TARGET_OS_HAS_SYSCTLBYNAME
#define BOTAN_TARGET_OS_HAS_THREAD_LOCAL
#define BOTAN_TARGET_OS_HAS_THREADS


#define BOTAN_BUILD_COMPILER_IS_XCODE

#define BOTAN_USE_GCC_INLINE_ASM



#define BOTAN_TARGET_ARCH "x86_64"
#define BOTAN_TARGET_ARCH_IS_X86_64
#define BOTAN_TARGET_CPU_IS_LITTLE_ENDIAN
#define BOTAN_TARGET_CPU_IS_X86_FAMILY
#define BOTAN_TARGET_CPU_HAS_NATIVE_64BIT

#define BOTAN_TARGET_SUPPORTS_AESNI
#define BOTAN_TARGET_SUPPORTS_AVX2
#define BOTAN_TARGET_SUPPORTS_AVX512
#define BOTAN_TARGET_SUPPORTS_BMI2
#define BOTAN_TARGET_SUPPORTS_RDRAND
#define BOTAN_TARGET_SUPPORTS_RDSEED
#define BOTAN_TARGET_SUPPORTS_SHA
#define BOTAN_TARGET_SUPPORTS_SSE2
#define BOTAN_TARGET_SUPPORTS_SSE41
#define BOTAN_TARGET_SUPPORTS_SSSE3






/**
 * @}
 */

/**
 * @ingroup buildinfo
 * @defgroup buildinfo_modules Enabled modules and API versions
 * @{
 */

/*
* Module availability definitions
*/
#define BOTAN_HAS_ADLER32 20131128
#define BOTAN_HAS_AEAD_CCM 20131128
#define BOTAN_HAS_AEAD_CHACHA20_POLY1305 20180807
#define BOTAN_HAS_AEAD_EAX 20131128
#define BOTAN_HAS_AEAD_GCM 20131128
#define BOTAN_HAS_AEAD_MODES 20131128
#define BOTAN_HAS_AEAD_OCB 20131128
#define BOTAN_HAS_AEAD_SIV 20131202
#define BOTAN_HAS_AES 20131128
#define BOTAN_HAS_AES_CRYSTALS_XOF 20230816
#define BOTAN_HAS_AES_NI 20131128
#define BOTAN_HAS_AES_VPERM 20190901
#define BOTAN_HAS_ANSI_X919_MAC 20131128
#define BOTAN_HAS_ARGON2 20210407
#define BOTAN_HAS_ARGON2_AVX2 20221216
#define BOTAN_HAS_ARGON2_FMT 20210407
#define BOTAN_HAS_ARGON2_SSSE3 20220303
#define BOTAN_HAS_ARIA 20170415
#define BOTAN_HAS_ASN1 20201106
#define BOTAN_HAS_AUTO_RNG 20161126
#define BOTAN_HAS_AUTO_SEEDING_RNG 20160821
#define BOTAN_HAS_BASE32_CODEC 20180418
#define BOTAN_HAS_BASE58_CODEC 20181209
#define BOTAN_HAS_BASE64_CODEC 20131128
#define BOTAN_HAS_BCRYPT 20131128
#define BOTAN_HAS_BIGINT 20240529
#define BOTAN_HAS_BIGINT_MP 20151225
#define BOTAN_HAS_BLAKE2B 20130131
#define BOTAN_HAS_BLAKE2BMAC 20201123
#define BOTAN_HAS_BLAKE2S 20231028
#define BOTAN_HAS_BLOCK_CIPHER 20131128
#define BOTAN_HAS_BLOWFISH 20180718
#define BOTAN_HAS_CAMELLIA 20150922
#define BOTAN_HAS_CASCADE 20131128
#define BOTAN_HAS_CAST 20131128
#define BOTAN_HAS_CAST_128 20171203
#define BOTAN_HAS_CERTSTOR_FLATFILE 20190410
#define BOTAN_HAS_CERTSTOR_MACOS 20190207
#define BOTAN_HAS_CERTSTOR_SQL 20160818
#define BOTAN_HAS_CERTSTOR_SYSTEM 20190411
#define BOTAN_HAS_CHACHA 20180807
#define BOTAN_HAS_CHACHA_AVX2 20180418
#define BOTAN_HAS_CHACHA_AVX512 20230101
#define BOTAN_HAS_CHACHA_RNG 20170728
#define BOTAN_HAS_CHACHA_SIMD32 20181104
#define BOTAN_HAS_CIPHER_MODES 20180124
#define BOTAN_HAS_CIPHER_MODE_PADDING 20131128
#define BOTAN_HAS_CMAC 20131128
#define BOTAN_HAS_CODEC_FILTERS 20131128
#define BOTAN_HAS_COMB4P 20131128
#define BOTAN_HAS_CPUID 20170917
#define BOTAN_HAS_CRC24 20131128
#define BOTAN_HAS_CRC32 20131128
#define BOTAN_HAS_CRYPTO_BOX 20131128
#define BOTAN_HAS_CSHAKE_XOF 20230911
#define BOTAN_HAS_CTR_BE 20131128
#define BOTAN_HAS_CURVE_25519 20170621
#define BOTAN_HAS_CURVE_448_UTILS 20240301
#define BOTAN_HAS_DES 20200926
#define BOTAN_HAS_DIFFIE_HELLMAN 20131128
#define BOTAN_HAS_DILITHIUM 20221018
#define BOTAN_HAS_DILITHIUM_AES 20221018
#define BOTAN_HAS_DILITHIUM_COMMON 20221018
#define BOTAN_HAS_DILITHIUM_ROUND3 20240916
#define BOTAN_HAS_DILITHIUM_SHAKE_XOF 20240728
#define BOTAN_HAS_DLIES 20160713
#define BOTAN_HAS_DL_GROUP 20131128
#define BOTAN_HAS_DL_SCHEME 20230101
#define BOTAN_HAS_DSA 20131128
#define BOTAN_HAS_DYNAMIC_LOADER 20160310
#define BOTAN_HAS_ECC_GROUP 20240531
#define BOTAN_HAS_ECC_KEY 20190801
#define BOTAN_HAS_ECC_PUBLIC_KEY_CRYPTO 20131128
#define BOTAN_HAS_ECDH 20131128
#define BOTAN_HAS_ECDSA 20131128
#define BOTAN_HAS_ECGDSA 20160301
#define BOTAN_HAS_ECIES 20160128
#define BOTAN_HAS_ECKCDSA 20160413
#define BOTAN_HAS_EC_CURVE_GFP 20240531
#define BOTAN_HAS_EC_HASH_TO_CURVE 20210420
#define BOTAN_HAS_ED25519 20170607
#define BOTAN_HAS_ED448 20240223
#define BOTAN_HAS_ELGAMAL 20131128
#define BOTAN_HAS_EME_OAEP 20180305
#define BOTAN_HAS_EME_PKCS1 20190426
#define BOTAN_HAS_EME_PKCS1v15 20131128
#define BOTAN_HAS_EME_RAW 20150313
#define BOTAN_HAS_EMSA_PKCS1 20140118
#define BOTAN_HAS_EMSA_PSSR 20131128
#define BOTAN_HAS_EMSA_RAW 20131128
#define BOTAN_HAS_EMSA_X931 20140118
#define BOTAN_HAS_ENTROPY_SOURCE 20151120
#define BOTAN_HAS_ENTROPY_SRC_GETENTROPY 20170327
#define BOTAN_HAS_ENTROPY_SRC_RDSEED 20151218
#define BOTAN_HAS_FFI 20240408
#define BOTAN_HAS_FILTERS 20160415
#define BOTAN_HAS_FPE_FE1 20131128
#define BOTAN_HAS_FRODOKEM 20230801
#define BOTAN_HAS_FRODOKEM_AES 20231103
#define BOTAN_HAS_FRODOKEM_SHAKE 20231114
#define BOTAN_HAS_GHASH 20201002
#define BOTAN_HAS_GHASH_CLMUL_CPU 20201002
#define BOTAN_HAS_GHASH_CLMUL_VPERM 20201002
#define BOTAN_HAS_GMAC 20160207
#define BOTAN_HAS_GOST_28147_89 20131128
#define BOTAN_HAS_GOST_34_10_2001 20131128
#define BOTAN_HAS_GOST_34_10_2012 20190801
#define BOTAN_HAS_GOST_34_11 20131128
#define BOTAN_HAS_HASH 20180112
#define BOTAN_HAS_HASH_ID 20131128
#define BOTAN_HAS_HEX_CODEC 20131128
#define BOTAN_HAS_HKDF 20170927
#define BOTAN_HAS_HMAC 20131128
#define BOTAN_HAS_HMAC_DRBG 20140319
#define BOTAN_HAS_HOTP 20180816
#define BOTAN_HAS_HSS_LMS 20230925
#define BOTAN_HAS_HTTP_UTIL 20171003
#define BOTAN_HAS_IDEA 20131128
#define BOTAN_HAS_IDEA_SSE2 20131128
#define BOTAN_HAS_ISO_9796 20161121
#define BOTAN_HAS_KDF1 20131128
#define BOTAN_HAS_KDF1_18033 20160128
#define BOTAN_HAS_KDF2 20131128
#define BOTAN_HAS_KDF_BASE 20131128
#define BOTAN_HAS_KECCAK 20131128
#define BOTAN_HAS_KECCAK_PERM 20230613
#define BOTAN_HAS_KECCAK_PERM_BMI2 20230612
#define BOTAN_HAS_KMAC 20230601
#define BOTAN_HAS_KUZNYECHIK 20230820
#define BOTAN_HAS_KYBER 20220107
#define BOTAN_HAS_KYBER_90S 20220107
#define BOTAN_HAS_KYBER_COMMON 20220107
#define BOTAN_HAS_KYBER_ROUND3 20240117
#define BOTAN_HAS_LION 20131128
#define BOTAN_HAS_LOCKING_ALLOCATOR 20131128
#define BOTAN_HAS_MAC 20150626
#define BOTAN_HAS_MCELIECE 20150922
#define BOTAN_HAS_MD4 20131128
#define BOTAN_HAS_MD5 20131128
#define BOTAN_HAS_MDX_HASH_FUNCTION 20131128
#define BOTAN_HAS_MEM_POOL 20180309
#define BOTAN_HAS_MGF1 20140118
#define BOTAN_HAS_ML_DSA 20240729
#define BOTAN_HAS_ML_KEM 20240821
#define BOTAN_HAS_MODES 20150626
#define BOTAN_HAS_MODE_CBC 20131128
#define BOTAN_HAS_MODE_CFB 20131128
#define BOTAN_HAS_MODE_XTS 20131128
#define BOTAN_HAS_NIST_KEYWRAP 20171119
#define BOTAN_HAS_NOEKEON 20131128
#define BOTAN_HAS_NOEKEON_SIMD 20160903
#define BOTAN_HAS_NUMBERTHEORY 20201108
#define BOTAN_HAS_OCSP 20201106
#define BOTAN_HAS_OFB 20131128
#define BOTAN_HAS_PARALLEL_HASH 20131128
#define BOTAN_HAS_PASSHASH9 20131128
#define BOTAN_HAS_PASSWORD_HASHING 20210419
#define BOTAN_HAS_PBKDF 20180902
#define BOTAN_HAS_PBKDF2 20180902
#define BOTAN_HAS_PBKDF_BCRYPT 20190531
#define BOTAN_HAS_PCURVES 20240404
#define BOTAN_HAS_PCURVES_BRAINPOOL256R1 20240608
#define BOTAN_HAS_PCURVES_BRAINPOOL384R1 20240608
#define BOTAN_HAS_PCURVES_BRAINPOOL512R1 20240608
#define BOTAN_HAS_PCURVES_FRP256V1 20240608
#define BOTAN_HAS_PCURVES_IMPL 20240714
#define BOTAN_HAS_PCURVES_NUMSP512D1 20240723
#define BOTAN_HAS_PCURVES_SECP192R1 20240709
#define BOTAN_HAS_PCURVES_SECP224R1 20240716
#define BOTAN_HAS_PCURVES_SECP256K1 20240608
#define BOTAN_HAS_PCURVES_SECP256R1 20240608
#define BOTAN_HAS_PCURVES_SECP384R1 20240608
#define BOTAN_HAS_PCURVES_SECP521R1 20240608
#define BOTAN_HAS_PCURVES_SM2P256V1 20240608
#define BOTAN_HAS_PEM_CODEC 20131128
#define BOTAN_HAS_PGP_S2K 20170527
#define BOTAN_HAS_PIPE_UNIXFD_IO 20131128
#define BOTAN_HAS_PKCS11 20160219
#define BOTAN_HAS_PKCS5_PBES2 20141119
#define BOTAN_HAS_PK_PADDING 20131128
#define BOTAN_HAS_POLY1305 20141227
#define BOTAN_HAS_POLY_DBL 20170927
#define BOTAN_HAS_PQCRYSTALS 20240228
#define BOTAN_HAS_PROCESSOR_RNG 20200508
#define BOTAN_HAS_PSK_DB 20171119
#define BOTAN_HAS_PUBLIC_KEY_CRYPTO 20131128
#define BOTAN_HAS_RAW_HASH_FN 20230221
#define BOTAN_HAS_RC4 20131128
#define BOTAN_HAS_RFC3394_KEYWRAP 20131128
#define BOTAN_HAS_RFC4880 20210407
#define BOTAN_HAS_RFC6979_GENERATOR 20140321
#define BOTAN_HAS_RIPEMD_160 20131128
#define BOTAN_HAS_ROUGHTIME 20190220
#define BOTAN_HAS_RSA 20160730
#define BOTAN_HAS_SALSA20 20171114
#define BOTAN_HAS_SCRYPT 20180902
#define BOTAN_HAS_SEED 20131128
#define BOTAN_HAS_SERPENT 20131128
#define BOTAN_HAS_SERPENT_AVX2 20180824
#define BOTAN_HAS_SERPENT_AVX512 20230101
#define BOTAN_HAS_SERPENT_SIMD 20160903
#define BOTAN_HAS_SHA1 20131128
#define BOTAN_HAS_SHA1_SSE2 20160803
#define BOTAN_HAS_SHA1_X86_SHA_NI 20170518
#define BOTAN_HAS_SHA2_32 20131128
#define BOTAN_HAS_SHA2_32_X86 20170518
#define BOTAN_HAS_SHA2_32_X86_BMI2 20180526
#define BOTAN_HAS_SHA2_64 20131128
#define BOTAN_HAS_SHA2_64_BMI2 20190117
#define BOTAN_HAS_SHA3 20161018
#define BOTAN_HAS_SHACAL2 20170813
#define BOTAN_HAS_SHACAL2_AVX2 20180826
#define BOTAN_HAS_SHACAL2_SIMD 20170813
#define BOTAN_HAS_SHACAL2_X86 20170814
#define BOTAN_HAS_SHAKE 20161009
#define BOTAN_HAS_SHAKE_CIPHER 20161018
#define BOTAN_HAS_SHAKE_XOF 20230815
#define BOTAN_HAS_SIMD_32 20131128
#define BOTAN_HAS_SIMD_AVX2 20180824
#define BOTAN_HAS_SIMD_AVX512 20230101
#define BOTAN_HAS_SIPHASH 20150110
#define BOTAN_HAS_SKEIN_512 20131128
#define BOTAN_HAS_SLH_DSA_WITH_SHA2 20240806
#define BOTAN_HAS_SLH_DSA_WITH_SHAKE 20240808
#define BOTAN_HAS_SM2 20180801
#define BOTAN_HAS_SM3 20170402
#define BOTAN_HAS_SM4 20170716
#define BOTAN_HAS_SOCKETS 20171216
#define BOTAN_HAS_SODIUM_API 20190615
#define BOTAN_HAS_SP800_108 20160128
#define BOTAN_HAS_SP800_56A 20170501
#define BOTAN_HAS_SP800_56C 20160211
#define BOTAN_HAS_SPHINCS_PLUS_COMMON 20230426
#define BOTAN_HAS_SPHINCS_PLUS_SHA2_BASE 20240807
#define BOTAN_HAS_SPHINCS_PLUS_SHAKE_BASE 20240809
#define BOTAN_HAS_SPHINCS_PLUS_WITH_SHA2 20230531
#define BOTAN_HAS_SPHINCS_PLUS_WITH_SHAKE 20230531
#define BOTAN_HAS_SRP6 20161017
#define BOTAN_HAS_STATEFUL_RNG 20160819
#define BOTAN_HAS_STREAM_CIPHER 20131128
#define BOTAN_HAS_STREEBOG 20170623
#define BOTAN_HAS_SYSTEM_RNG 20141202
#define BOTAN_HAS_THREAD_UTILS 20190922
#define BOTAN_HAS_THREEFISH_512 20131224
#define BOTAN_HAS_THRESHOLD_SECRET_SHARING 20131128
#define BOTAN_HAS_TLS 20201128
#define BOTAN_HAS_TLS_12 20210608
#define BOTAN_HAS_TLS_13 20210721
#define BOTAN_HAS_TLS_13_PQC 20230919
#define BOTAN_HAS_TLS_CBC 20161008
#define BOTAN_HAS_TLS_SESSION_MANAGER_SQL_DB 20141219
#define BOTAN_HAS_TLS_V12_PRF 20131128
#define BOTAN_HAS_TOTP 20180816
#define BOTAN_HAS_TREE_HASH 20231006
#define BOTAN_HAS_TRUNCATED_HASH 20230215
#define BOTAN_HAS_TWOFISH 20131128
#define BOTAN_HAS_UTIL_FUNCTIONS 20180903
#define BOTAN_HAS_UUID 20180930
#define BOTAN_HAS_WHIRLPOOL 20131128
#define BOTAN_HAS_X25519 20240412
#define BOTAN_HAS_X448 20240219
#define BOTAN_HAS_X509 20201106
#define BOTAN_HAS_X509_CERTIFICATES 20201106
#define BOTAN_HAS_X942_PRF 20131128
#define BOTAN_HAS_XMD 20240404
#define BOTAN_HAS_XMSS_RFC8391 20201101
#define BOTAN_HAS_XOF 20230815
#define BOTAN_HAS_ZFEC 20211211
#define BOTAN_HAS_ZFEC_SSE2 20211211
#define BOTAN_HAS_ZFEC_VPERM 20211211


/**
 * @}
 */

/**
 * @addtogroup buildinfo_configuration
 * @{
 */

/** Local/misc configuration options (if any) follow */


/*
* Things you can edit (but probably shouldn't)
*/

/** How much to allocate for a buffer of no particular size */
#define BOTAN_DEFAULT_BUFFER_SIZE 4096

#if defined(BOTAN_HAS_VALGRIND) || defined(BOTAN_ENABLE_DEBUG_ASSERTS)
   /**
    * @brief Prohibits access to unused memory pages in Botan's memory pool
    *
    * If BOTAN_MEM_POOL_USE_MMU_PROTECTIONS is defined, the Memory_Pool
    * class used for mlock'ed memory will use OS calls to set page
    * permissions so as to prohibit access to pages on the free list, then
    * enable read/write access when the page is set to be used. This will
    * turn (some) use after free bugs into a crash.
    *
    * The additional syscalls have a substantial performance impact, which
    * is why this option is not enabled by default. It is used when built for
    * running in valgrind or debug assertions are enabled.
    */
   #define BOTAN_MEM_POOL_USE_MMU_PROTECTIONS
#endif

#if defined(BOTAN_HAS_VALGRIND)
   /**
    * If `BOTAN_CT_POISON_ENABLED` is defined, then the `CT::poison` and
    * `CT::unpoison` functions have an effect and do not just compile to no-ops.
    *
    * At the moment that is only the case when building with valgrind support. We
    * could potentially add support for other tools in the future.
    */
   #define BOTAN_CT_POISON_ENABLED
#endif

/**
* If enabled uses memset via volatile function pointer to zero memory,
* otherwise does a byte at a time write via a volatile pointer.
*/
#define BOTAN_USE_VOLATILE_MEMSET_FOR_ZERO 1

/**
* Normally blinding is performed by choosing a random starting point (plus
* its inverse, of a form appropriate to the algorithm being blinded), and
* then choosing new blinding operands by successive squaring of both
* values. This is much faster than computing a new starting point but
* introduces some possible corelation
*
* To avoid possible leakage problems in long-running processes, the blinder
* periodically reinitializes the sequence. This value specifies how often
* a new sequence should be started.
*/
#define BOTAN_BLINDING_REINIT_INTERVAL 64

/**
* Userspace RNGs like HMAC_DRBG will reseed after a specified number
* of outputs are generated. Set to zero to disable automatic reseeding.
*/
#define BOTAN_RNG_DEFAULT_RESEED_INTERVAL 1024

/** Number of entropy bits polled for reseeding userspace RNGs like HMAC_DRBG */
#define BOTAN_RNG_RESEED_POLL_BITS 256

#define BOTAN_RNG_RESEED_DEFAULT_TIMEOUT std::chrono::milliseconds(50)

/**
* Specifies (in order) the list of entropy sources that will be used
* to seed an in-memory RNG.
*/
#define BOTAN_ENTROPY_DEFAULT_SOURCES \
   { "rdseed", "hwrng", "getentropy", "system_rng", "system_stats" }

/** Multiplier on a block cipher's native parallelism */
#define BOTAN_BLOCK_CIPHER_PAR_MULT 4

/**
 * @}
 */

/* Check for a common build problem */

#if defined(BOTAN_TARGET_ARCH_IS_X86_64) && ((defined(_MSC_VER) && !defined(_WIN64)) || \
                                             (defined(__clang__) && !defined(__x86_64__)) || \
                                             (defined(__GNUG__) && !defined(__x86_64__)))
    #error "Trying to compile Botan configured as x86_64 with non-x86_64 compiler."
#endif

#if defined(BOTAN_TARGET_ARCH_IS_X86_32) && ((defined(_MSC_VER) && defined(_WIN64)) || \
                                             (defined(__clang__) && !defined(__i386__)) || \
                                             (defined(__GNUG__) && !defined(__i386__)))

    #error "Trying to compile Botan configured as x86_32 with non-x86_32 compiler."
#endif

#endif
