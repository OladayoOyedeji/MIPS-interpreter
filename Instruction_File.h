#ifndef TEXT_FILE_H
#define TEXT_FILE_H

// void load_imediate(int32_t * registers[], int size);
// void load_address(int32_t * registers[], int size);
// void load_word(int32_t * registers[], int size);
// void load_byte(int32_t * registers[], int size);
// void move(int32_t * registers[], int size);
// void load_imediate(int32_t * registers[], int size);
// void load_imediate(int32_t * registers[], int size);
// void load_imediate(int32_t * registers[], int size);
// void load_imediate(int32_t * registers[], int size);
// void load_imediate(int32_t * registers[], int size);
// void load_imediate(int32_t * registers[], int size);
// void load_imediate(int32_t * registers[], int size);
// void load_imediate(int32_t * registers[], int size);
// void load_imediate(int32_t * registers[], int size);
// void load_imediate(int32_t * registers[], int size);
// void load_imediate(int32_t * registers[], int size);
// void load_imediate(int32_t * registers[], int size);
// void load_imediate(int32_t * registers[], int size);
// void load_imediate(int32_t * registers[], int size);
// void load_imediate(int32_t * registers[], int size);
// void load_imediate(int32_t * registers[], int size);
// void load_imediate(int32_t * registers[], int size);
// void load_imediate(int32_t * registers[], int size);
// void load_imediate(int32_t * registers[], int size);

class TextFile
{
    TextFile();
    std::map<unsigned char, void (*) (int32_t **, int)> instructions_;
    std::vector< unsigned char * > instruction
};

#endif
