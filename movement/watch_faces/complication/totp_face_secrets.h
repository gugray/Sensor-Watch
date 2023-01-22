static const uint8_t num_keys = 6;
static uint8_t keys[] = {
    // 32 bytes, for Amazon
    0x63, 0xca, 0xa2, 0x75, 0x92, 0x39, 0xc2, 0x0c, 0x6f, 0x12, 0x8a, 0xc1, 0xaf, 0x5f, 0x52, 0x4d,
    0x62, 0x83, 0xea, 0x97, 0xbb, 0x44, 0xe8, 0xc9, 0x2b, 0xb9, 0x4e, 0xf7, 0xf5, 0x76, 0x44, 0x92,
    // 10 bytes, for Github
    0xdb, 0x90, 0x9f, 0x3f, 0xa6, 0x29, 0x1f, 0xe0, 0xd0, 0x70,
    // 10 bytes, for memoQ
    0x9e, 0x58, 0xac, 0xf9, 0xba, 0x7d, 0xb5, 0x70, 0xc2, 0x03,
    // 10 bytes, for PayPal
    0x34, 0x90, 0x72, 0x53, 0xfe, 0xf5, 0xbd, 0x9c, 0xcb, 0x88,
    // 20 bytes, for DigitalOcean
    0x20, 0x8a, 0x3a, 0xda, 0x19, 0x60, 0x56, 0xd7, 0xad, 0xde,
    0xb9, 0x00, 0xce, 0x82, 0xf1, 0x12, 0x4b, 0xa5, 0xc5, 0x55,
    // 16 bytes, for DropBox
    0x36, 0xfc, 0xfa, 0x07, 0x99, 0x6b, 0x05, 0xce, 0x22, 0x2e, 0x4f, 0xf2, 0xf6, 0x2f, 0x11, 0xef,
};
static const uint8_t key_sizes[] = {
    32,
    10,
    10,
    10,
    20,
    16,
};
static const uint32_t timesteps[] = {
    30,
    30,
    30,
    30,
    30,
    30,
};
static const char labels[][2] = {
    { 'a', 'z' },
    { 'g', 'h' },
    { 'm', 'q' },
    { 'P', 'P' },
    { 'd', '0' },
    { 'd', 'b' },
};

static const hmac_alg algorithms[] = {
    SHA1,
    SHA1,
    SHA1,
    SHA1,
    SHA1,
    SHA1,
};
