// file: seven_seg.h

#ifndef SEVEN_SEG_H
#define SEVEN_SEG_H

// See the accompanying main.cpp on how to use the console() function.
//
// The following is a 7 segment display:
//
//    a
//   b c
//    d
//   e f
//    g
//
// a,b,c,d,e,f,g are all 0 or 1. If all are 1, the display is
//
//    -
//   | |
//    -
//   | |
//    -
//
typedef std::vector< std::string > seg7_t;

void console(std::vector< std::tuple< int, int, std::vector< std::string > > > data)
{
    int rows = 5;
    int cols = 80;
    std::vector< std::string > output(rows, std::string(cols, ' '));
    if (data.size() > 16)
    {
        std::cout << "\nconsole error: data.size() too large\n" << std::endl;
        throw -1;
    }
    for (auto & e: data)
    {
        int r = std::get<0>(e);
        int c = std::get<1>(e);
        std::vector< std::string > ss = std::get<2>(e);
        for (auto & s: ss)
        {
            output[r++].replace(c, s.size(), s);
        }
    }
    for (int i = 0; i < cols + 2; ++i) std::cout << '#';
    std::cout << '\n';
    for (auto & e: output)
    {
        std::cout << '#' << e << '#' << '\n';
    }
    for (int i = 0; i < cols + 2; ++i) std::cout << '#';
    std::cout << '\n';
}

std::vector< std::string > seg7(std::vector< int > in)
{
    std::vector< std::string > s = {" - ",
                                    "| |",
                                    " - ",
                                    "| |",
                                    " - "};
    std::vector< std::pair< int, int > > indices = {{0,1},
                                                    {1,0}, {1,2},
                                                    {2,1},
                                                    {3,0}, {3,2},
                                                    {4,1}};
    for (auto && e: boost::combine(in, indices))
    {
        int bit;
        std::pair< int, int > rc;
        boost::tie(bit, rc) = e;
        if (bit == 0)
        {
            int r = rc.first, c = rc.second;
            s[r][c] = ' ';
        }
    }
    std::vector< std::string > ret;
    for (auto & e: s)
    {
        ret.push_back(e);
    }
    return ret;
}

void seg7array(std::vector< seg7_t > data)
{
    std::vector< std::tuple< int, int, seg7_t > > t;
    int c = 1;
    for (auto & e: data)
    {
        t.push_back({0, c, e});
        c += 5;
    }
    console(t);
}

#endif
