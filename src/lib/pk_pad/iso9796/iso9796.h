/*
 * ISO-9796-2 - Digital signature schemes giving message recovery schemes 2 and 3
 * (C) 2016 Tobias Niemann, Hackmanit GmbH
 *
 * Botan is released under the Simplified BSD License (see license.txt)
 */

#ifndef BOTAN_ISO9796_H__
#define BOTAN_ISO9796_H__

#include <botan/emsa.h>
#include <botan/hash.h>

namespace Botan {

/**
* ISO-9796-2 - Digital signature scheme 2 (probabilistic)
*/
class BOTAN_DLL ISO_9796_DS2 final : public EMSA
   {
   public:
      /**
       * @param hash function to use
       * @param use implicit ISO trailer
       */
      explicit ISO_9796_DS2(HashFunction* hash, bool implicit = false) : m_hash(hash), m_implicit(implicit),
         m_SALT_SIZE(hash->output_length()) {}

      /**
       * @param hash function to use
       * @param whether or not the trailer is implicit
       * @param size of the salt to use in bytes
       */
      ISO_9796_DS2(HashFunction* hash, bool implicit, size_t salt_size) : m_hash(hash), m_implicit(implicit),
         m_SALT_SIZE(salt_size) {}

      EMSA* clone() override
         {return new ISO_9796_DS2(m_hash->clone(), m_implicit, m_SALT_SIZE);}
   private:
      void update(const byte input[], size_t length) override;

      secure_vector<byte> raw_data() override;

      secure_vector<byte> encoding_of(const secure_vector<byte>& msg,
                                      size_t output_bits,
                                      RandomNumberGenerator& rng) override;

      bool verify(const secure_vector<byte>& coded,
                  const secure_vector<byte>& raw,
                  size_t key_bits) override;

      std::unique_ptr<HashFunction> m_hash;
      bool m_implicit;
      size_t m_SALT_SIZE;
      secure_vector<byte> m_msg_buffer;
   };

/**
* ISO-9796-2 - Digital signature scheme 3 (deterministic)
*/
class BOTAN_DLL ISO_9796_DS3 final : public EMSA
   {
   public:
      /**
       * @param hash function to use
       * @param whether or not the trailer is implicit
       */
      ISO_9796_DS3(HashFunction* hash, bool implicit = false) : m_hash(hash), m_implicit(implicit)
         {}

      EMSA* clone() override
         {return new ISO_9796_DS3(m_hash->clone(), m_implicit);}
   private:
      void update(const byte input[], size_t length) override;

      secure_vector<byte> raw_data() override;

      secure_vector<byte> encoding_of(const secure_vector<byte>& msg,
                                      size_t output_bits,
                                      RandomNumberGenerator& rng) override;

      bool verify(const secure_vector<byte>& coded,
                  const secure_vector<byte>& raw,
                  size_t key_bits) override;

      std::unique_ptr<HashFunction> m_hash;
      bool m_implicit;
      secure_vector<byte> m_msg_buffer;
   };

}

#endif

