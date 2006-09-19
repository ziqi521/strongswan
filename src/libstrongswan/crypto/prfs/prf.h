/**
 * @file prf.h
 * 
 * @brief Interface prf_t.
 * 
 */

/*
 * Copyright (C) 2005-2006 Martin Willi
 * Copyright (C) 2005 Jan Hutter
 * Hochschule fuer Technik Rapperswil
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.  See <http://www.fsf.org/copyleft/gpl.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */

#ifndef PRF_H_
#define PRF_H_

#include <types.h>

typedef enum pseudo_random_function_t pseudo_random_function_t;

/**
 * @brief Pseudo random function, as in IKEv2 RFC 3.3.2.
 * 
 * Currently only the following algorithms are implemented:
 * - PRF_HMAC_MD5
 * - PRF_HMAC_SHA1
 * 
 * @ingroup prfs
 */
enum pseudo_random_function_t {
	PRF_UNDEFINED = 1024,
	/** Implemented via hmac_prf_t. */
	PRF_HMAC_MD5 = 1,
	/** Implemented via hmac_prf_t. */
	PRF_HMAC_SHA1 = 2,
	PRF_HMAC_TIGER = 3,
	PRF_AES128_CBC = 4,
};

/** 
 * String mappings for encryption_algorithm_t.
 */
extern mapping_t pseudo_random_function_m[];


typedef struct prf_t prf_t;

/**
 * @brief Generic interface for pseudo-random-functions.
 * 
 * @b Constructors:
 *  - prf_create()
 *  - hmac_prf_create()
 * 
 * @todo Implement more prf algorithms
 * 
 * @ingroup prfs
 */
struct prf_t {
	/**
	 * @brief Generates pseudo random bytes and writes them in the buffer.
	 *
	 * @param this			calling object
	 * @param seed			a chunk containing the seed for the next bytes
	 * @param[out] buffer	pointer where the generated bytes will be written
	 */
	void (*get_bytes) (prf_t *this, chunk_t seed, u_int8_t *buffer);
	
	/**
	 * @brief Generates pseudo random bytes and allocate space for them.
	 * 
	 * @param this			calling object
	 * @param seed			a chunk containing the seed for the next bytes
	 * @param[out] chunk	chunk which will hold generated bytes
	 */
	void (*allocate_bytes) (prf_t *this, chunk_t seed, chunk_t *chunk);
	
	/**
	 * @brief Get the block size of this prf_t object.
	 * 
	 * @param this			calling object
	 * @return				block size in bytes
	 */
	size_t (*get_block_size) (prf_t *this);
	
	/**
	 * @brief Get the key size of this prf_t object.
	 * 
	 * @param this			calling object
	 * @return				key size in bytes
	 */
	size_t (*get_key_size) (prf_t *this);
	
	/**
	 * @brief Set the key for this prf_t object.
	 * 
	 * @param this			calling object
	 * @param key			key to set
	 */
	void (*set_key) (prf_t *this, chunk_t key);
	
	/**
	 * @brief Destroys a prf object.
	 *
	 * @param this 			calling object
	 */
	void (*destroy) (prf_t *this);
};

/**
 * @brief Generic constructor for a prf_t oject.
 * 
 * @param pseudo_random_function	Algorithm to use
 * @return
 * 									- prf_t object
 * 									- NULL if prf algorithm not supported
 *
 * @ingroup prfs
 */
prf_t *prf_create(pseudo_random_function_t pseudo_random_function);

#endif /*PRF_H_*/
