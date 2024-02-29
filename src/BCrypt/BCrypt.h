#include "EksBlowfish.h"
#include "base64.h"
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <sys/types.h>
#include <tuple>

std::string generateBase64(unsigned char **bytes);

unsigned char **generateBytes(uint64_t *encryptedText);
