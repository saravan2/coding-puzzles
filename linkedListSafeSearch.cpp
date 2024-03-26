// ROM contents
// Tuple Header (3 (2 byte words) = 6 bytes)
// 1: id
// 2: offset of next ptr (units of bytes, all 1s no next)
// 3: payload length in bytes - 16 bit 
// Variable Payload


struct tuple_header {
  uint16_t id;
  uint16_t offset;
  uint16_t payload_len;
};

#define ROM_SIZE 65536
// ROM = 65536 / 6

// Finds payload of tuple with given id
uint16_t *find_tuple(const uint16_t *rom, uint16_t id, size_t *len) {
  uint16_t sentinel = 0xffff;
  struct tuple_header *th = (struct tuple_header *)rom;
  uint16_t * payload = NULL;
  uint16_t count = 0;
  uint16_t max = ROM_SIZE / sizeof(struct tuple_header); 
  for(;;) {
    if(th->id == id) {
      *len = th->payload_len;
      payload = (uint16_t *)(++th);
      return payload;
    }
    if (th->offset == sentinel) {
      return payload;
    }
    th = (struct tuple_header *)((char *)rom + th->offset);
    count++;
    if (count > max) {
      break;
    }
  }
  return payload;
}