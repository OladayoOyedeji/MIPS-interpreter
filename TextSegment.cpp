#include "TextSegment.h"


void TextSegment::print_addressh(int i) const
{
    if (i > size_)
    {
        throw SizeError();
    }
    std::cout << "0x" << std::setw(8) << std::setfill('0')
              << std::right << std::hex << (starting_address_ + i * 4);
}

void TextSegment::insert(const std::vector< std::string > & token)
{
    // if (size_ == MAX_TEXTSEGMENT_SIZE) throw SizeError();

    // if (token.size() == 0)
    // {
    // }
    // //===============================================================
    // // check if the operation is a pseudo instruction
    // //===============================================================
    // if (PSEUDO_INSTRUCTIONS.find(token[0]) != PSEUDO_INSTRUCTIONS.end())
    // {
    //     // iteration over list of vectors of strings
    //     for (auto p: PSEUDO_INSTRUCTIONS[token[0]])
    //     {
    //         // iteration over the vectors of string
    //         std::vector<std::string > & v = p;
    //         for (int i = 0; i < v.size(); ++i)
    //         {
    //             if (v[i].size() == 1 && v[i][0] >= '0' && v[i][0] <= '9')
    //             {
    //                 v[i] = token[v[i][0] - '0'];
    //             }
    //         }
    //         machine_format_.push_back(new MachineFormat(v));
    //         size_++;
    //         std::cout << v << std::endl;
    //     }
    // }
    // else
    // {
    //     try
    //     {
    //         machine_format_.push_back(new MachineFormat(token));
    //         size_++;
    //     }
    //     catch (const std::runtime_error & e)
    //     {
    //         std::cerr << "Invalid Instruction -> " << e.what() << std::endl;
    //         std::cout << machine_format_.size() << std::endl;
    //         throw std::runtime_error("Instruction not accepted");
    //     }
    // }
}
