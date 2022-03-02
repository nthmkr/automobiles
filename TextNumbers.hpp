#ifndef TEXTNUMBERS_HPP
#define TEXTNUMBERS_HPP

#include <stdint.h>
#include <iostream>

class TextNumbers {
public:
    TextNumbers() {}

    static constexpr unsigned kLimit{4000000000};
    static const std::string kFrom0To19[20];
    static const std::string kHundreds[10];
    static const std::string kDozens[10];
    static const std::string kOneTwoThousands[3];

    std::string parsing(const unsigned in)
    {
        if (in > kLimit)
        {
            return "Error: more than 4 billion!";
        }

        if (in == 0) {
           return "ноль автомобилей";
        }

        unsigned value{in};
        std::string out_str{};

        // Billions
        unsigned num = value / pow10(static_cast<uint8_t>(Things::Billions));
        if (num) {
            out_str += kFrom0To19[num] + " ";
            out_str += "миллиард" + ending(num, Things::Millions);
            value -= num * pow10(static_cast<uint8_t>(Things::Billions));
        }

        // Millions
        if (value >= 1000000) {
            num = calc_3_digits(out_str, value, static_cast<uint8_t>(Things::Millions));
            out_str += "миллион" + ending(num, Things::Millions);
        }

        // Thousands
        if (value >= 1000) {
            num = calc_3_digits(out_str, value, static_cast<uint8_t>(Things::Thousands));
            out_str += "тысяч" + ending(num, Things::Thousands);
        }

        // Units
        if (value > 0) {
            num = calc_3_digits(out_str, value, static_cast<uint8_t>(Things::Autos));
        } else {
            num = 0;
        }

        out_str += "автомобил" + ending(num, Things::Autos);

        return out_str;
    }

private:

    unsigned pow10(unsigned deg)
    {
        return deg ? 10 * pow10(deg - 1 ) : 1;
    }

    enum class Things : uint8_t {
        Billions = 9,
        Millions = 6,
        Thousands = 3,
        Autos = 0
    };

    std::string ending(unsigned qnt, Things thing)
    {
        if (qnt > 20) {
            std::cout << "Error! Must be less than 20." << std::endl;
            return "";
        }

        if (qnt == 1) {
            if (thing == Things::Millions) {
                return " ";
            } else if (thing == Things::Thousands) {
                return "а ";
            } else if (thing == Things::Autos) {
                return "ь ";
            }
        }
        else if (qnt >= 2 && qnt <= 4) {
            if (thing == Things::Millions) {
                return "a ";
            } else if (thing == Things::Thousands) {
                return "и ";
            } else if (thing == Things::Autos) {
                return "я ";
            }
        }
        else if ((qnt >= 5) || (qnt == 0)) {
            if (thing == Things::Millions) {
                return "ов ";
            } else if (thing == Things::Thousands) {
                return " ";
            } else if (thing == Things::Autos) {
                return "ей ";
            }
        }
    }

    unsigned calc_3_digits(std::string &str, unsigned &value, uint8_t digit_low)
    {
        // Hundreds
       unsigned numeral = value / pow10(digit_low + 2);
       if (numeral) {
           str += kHundreds[numeral] + " ";
           value -= numeral * pow10(digit_low + 2);
       }

       // Dozens and units
       numeral = value / pow10(digit_low + 1);
       if (numeral == 1) {
           value -= numeral * pow10(digit_low + 1);
           numeral = value / pow10(digit_low);
           value -= numeral * pow10(digit_low);
           numeral += 10;

           str += kFrom0To19[numeral] + " ";
       } else {
            if (numeral) {
                str += kDozens[numeral] + " ";
                value -= numeral * pow10(digit_low + 1);
            }

            numeral = value / pow10(digit_low);
            if (numeral) {
                if (static_cast<Things>(digit_low) == Things::Thousands &&
                        (numeral == 1 || numeral == 2)) {
                    str += kOneTwoThousands[numeral] + " ";
                } else {
                    str += kFrom0To19[numeral] + " ";
                }

                value -= numeral * pow10(static_cast<uint8_t>(digit_low));
            }
       }

       return numeral;
    }
};

#endif // TEXTNUMBERS_HPP
