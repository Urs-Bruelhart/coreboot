/* SPDX-License-Identifier: BSD-3-Clause */

/*
 * Functions for querying, manipulating and locking rollback indices
 * stored in the TPM NVRAM.
 */

#ifndef ANTIROLLBACK_H_
#define ANTIROLLBACK_H_

#include <types.h>
#include <security/tpm/tspi.h>
#include <vb2_sha.h>

struct vb2_context;
enum vb2_pcr_digest;

/* TPM NVRAM location indices. */
#define FIRMWARE_NV_INDEX               0x1007
#define KERNEL_NV_INDEX                 0x1008
/* 0x1009 used to be used as a backup space. Think of conflicts if you
 * want to use 0x1009 for something else. */
#define BACKUP_NV_INDEX                 0x1009
#define FWMP_NV_INDEX                   0x100a
#define REC_HASH_NV_INDEX               0x100b
#define REC_HASH_NV_SIZE                VB2_SHA256_DIGEST_SIZE

/* Structure definitions for TPM spaces */

/* Flags for firmware space */

/*
 * Last boot was developer mode.  TPM ownership is cleared when transitioning
 * to/from developer mode.
 */
#define FLAG_LAST_BOOT_DEVELOPER 0x01

/* All functions return TPM_SUCCESS (zero) if successful, non-zero if error */

uint32_t antirollback_read_space_firmware(struct vb2_context *ctx);

/**
 * Write may be called if the versions change.
 */
uint32_t antirollback_write_space_firmware(struct vb2_context *ctx);

/**
 * Read and write kernel space in TPM.
 */
uint32_t antirollback_read_space_kernel(struct vb2_context *ctx);
uint32_t antirollback_write_space_kernel(struct vb2_context *ctx);

/**
 * Lock must be called.
 */
uint32_t antirollback_lock_space_firmware(void);

/* Read recovery hash data from TPM. */
uint32_t antirollback_read_space_rec_hash(uint8_t *data, uint32_t size);
/* Write new hash data to recovery space in TPM. */
uint32_t antirollback_write_space_rec_hash(const uint8_t *data, uint32_t size);
/* Lock down recovery hash space in TPM. */
uint32_t antirollback_lock_space_rec_hash(void);

#endif  /* ANTIROLLBACK_H_ */
