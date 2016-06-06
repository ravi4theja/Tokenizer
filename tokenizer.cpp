#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main(int argc, char* argv[])
{
    string lines[1024];
    string line;
    int tidcount = 1, out_flag = 0, p_flag = 0;
    int i = 0, j = 0, p = 0;
    //cout << argc;
    //cout << argv[1] << "\n";
    
    while (getline(cin, line))
    {
        if (!line.empty())
        {
            lines[i] = line;
            i++;
        }
        else
        {
            i++;
            break;
        }
    }
    if (argc == 1)
    	out_flag = 0;
    else
    {	
    	string op(argv[1]);
    	if(op == "0")
    		out_flag = 0;
    	else if(op == "1")
    		out_flag = 1;
    	else if(op == "2")
    		out_flag = 2;
    	else
    	{
    		out_flag = 3;
    		cout << "TID: " << tidcount << ", TYPE: " << "97(ERR1)" << ", POS: 0"
        	<< ", LEN: 0" << "\n";
        	cout << "\n" << "Totals: " << "len = 0" << ", tokens = 1" << ", printed = 1" << "\n";
        }
    }
    if (out_flag == 0 || out_flag == 1 || out_flag == 2)
    {
        for (j = 0; j < 1024; j++)
        {
            if (!lines[j].empty())
            {
            	int new_flag = 0;
                for (int k = 0; k < lines[j].length();)
                {
                    string word = "";
                    
                    if (48 <= lines[j][k] && lines[j][k] <= 57)  //checking for an integer
                    {
                        while (lines[j][k] >= 48 && lines[j][k] <= 57 && lines[j][k] != 46 && k < lines[j].length())
                        {
                            word += lines[j][k];
                            k++;
                        }
                        if (lines[j][k] == 46)   //if there is a decimal point in between the integers
                        {
                            word += lines[j][k];
                            k++;
                            while (lines[j][k] >= 48 && lines[j][k] <= 57 && k < lines[j].length())
                            {
                                word += lines[j][k];
                                k++;
                            }
                            if (out_flag == 0 || out_flag == 1)
                            {
                                cout << "TID: " << tidcount << ", TYPE: " << "4(FLOAT)" << ", POS: "
                                << p + k - word.length() << ", LEN: " << word.length() << ", VALUE: " << word << "\n";
                                p_flag += 1;
                            }
                            tidcount++;
                        }
                        else
                        {
                            if (out_flag == 0 || out_flag == 1)
                            {
                                cout << "TID: " << tidcount << ", TYPE: " << "3(INT)" << ", POS: "
                                << p + k - word.length() << ", LEN: " << word.length() << ", VALUE: " << word << "\n";
                                p_flag += 1;
                            }
                            tidcount++;
                        }
                    }
                    else if (lines[j][k] == 46) // checking for a decimal point at the start
                    {
                        word += lines[j][k];
                        k++;
                        while (lines[j][k] >= 48 && lines[j][k] <= 57 && k < lines[j].length())
                        {
                            word += lines[j][k];
                            k++;
                        }
                        if (out_flag == 0 || out_flag == 1)
                        {
                            cout << "TID: " << tidcount << ", TYPE: " << "4(FLOAT)" << ", POS: "
                            << p + k - word.length() << ", LEN: " << word.length() << ", VALUE: " << word << "\n";
                            p_flag += 1;
                        }
                        tidcount++;
                    }
                    else if (lines[j][k] == 32 || lines[j][k] == 9)     //checking for a whitespace
                    {
                        while (lines[j][k] == 32 || lines[j][k] == 9 && k < lines[j].length())
                        {
                            word += lines[j][k];
                            k++;
                        }
                        if (out_flag == 0 || out_flag == 2)
                        {
                            cout << "TID: " << tidcount << ", TYPE: " << "5(WS)" << ", POS: "
                            << p + k - word.length() << ", LEN: " << word.length() << "\n";
                            p_flag += 1;
                        }
                        tidcount++;
                    }
                    else if (lines[j][k] == 34) // checking for quotation marks at the start
                    {
                        k += 1;
                        while (((lines[j][k] >= 20 && lines[j][k] <= 126) || lines[j][k] == 9 || lines[j][k] == 10)
                        && lines[j][k] != 34 && k < lines[j].length())
                        {
                            word += lines[j][k];
                            k++;
                        }
                        if (k == lines[j].length())   // if there are no ending quotation marks by the end of the line
                        {
                            if (!lines[j + 1].empty())
                            {
                                if (out_flag == 0 || out_flag == 2)
                                {
                                    cout << "TID: " << tidcount << ", TYPE: " << "98(ERR2)" << ", POS: "
                                    << p + k - word.length() - 1 << ", LEN: " << word.length() + 1 << "\n";
                                    p_flag += 1;
                                }
                                tidcount++;
                            }
                            else if (lines[j + 1].empty())
                            {
                            	new_flag = 1;
                                if (out_flag == 0 || out_flag == 2)
                                {
                                    cout << "TID: " << tidcount << ", TYPE: " << "98(ERR2)" << ", POS: "
                                    << p + k - word.length() - 1 << ", LEN: " << word.length() + 2 << "\n";
                                    p_flag += 1;
                                }
                                tidcount++;
                            }
                        }
                        else if (lines[j][k] == 34)  // if there are ending quotaion marks
                        {
                            if (out_flag == 0 || out_flag == 1)
                            {
                                cout << "TID: " << tidcount << ", TYPE: " << "2(STR)" << ", POS: "
                                << p + k - word.length() - 1 << ", LEN: " << word.length() + 2 << ", VALUE: " << word << "\n";
                                p_flag += 1;
                            }
                            tidcount++;
                            k++;
                        }
                        // checking if there is a bad character
                        else if ((lines[j][k] >= 0 && lines[j][k] <= 8) || (lines[j][k] >= 11 && lines[j][k] <= 31) || (lines[j][k] >= 127 && lines[j][k] <= 255))
                        {
                            if (out_flag == 0 || out_flag == 2)
                            {
                                cout << "TID: " << tidcount << ", TYPE: " << "98(ERR2)" << ", POS: "
                                << p + k - word.length() - 1 << ", LEN: " << word.length() + 1 << "\n";
                                p_flag += 1;
                            }
                            tidcount++;
                        }
                    }
                    //checking if there is a single or consecutive bad characters
                    else if ((lines[j][k] >= 0 && lines[j][k] <= 8) || (lines[j][k] >= 11 && lines[j][k] <= 31) || lines[j][k] == 127)
                    {
                        while ((lines[j][k] >= 0 && lines[j][k] <= 8) || (lines[j][k] >= 11 && lines[j][k] <= 31) || (lines[j][k] >= 127 && lines[j][k] <= 255))
                        {
                            word += lines[j][k];
                            k++;
                        }
                        if (out_flag == 0 || out_flag == 2)
                        {
                            cout << "TID: " << tidcount << ", TYPE: " << "99(ERR3)" << ", POS: "
                            << p + k - word.length() << ", LEN: " << word.length() << "\n";
                            p_flag += 1;
                        }
                        tidcount++;
                    }
                    else if (lines[j][k] == 35)  // checking for a comment at the start
                    {
                        for (; k <= lines[j].length(); k++)
                        {
                            word += lines[j][k];
                        }
                        if (out_flag == 0 || out_flag == 2)
                        {
                            cout << "TID: " << tidcount << ", TYPE: " << "7(COMMENT)" << ", POS: "
                            << p + k - word.length() << ", LEN: " << word.length() << ", VALUE: " << word << "\n";
                            p_flag += 1;
                        }
                        tidcount++;
                        break;
                    }
                    // checking if it's an underscore or a letter at the start
                    else if ((lines[j][k] >= 65 && lines[j][k] <= 91) ||
                    (lines[j][k] >= 97 && lines[j][k] <= 122) || lines[j][k] == 95)
                    {
                        int id_flag = 1;
                        word += lines[j][k];
                        k++;
                        // checking if it's an underscore or a letter or a number before the end of line
                        while ((lines[j][k] >= 65 && lines[j][k] <= 91) ||
                        (lines[j][k] >= 97 && lines[j][k] <= 122) || lines[j][k] == 95 || (lines[j][k] >= 48 && lines[j][k] <= 57) && k < lines[j].length())
                        {
                            word += lines[j][k];
                            // checking for for, while, if, else if the id didn't start with an underscore
                            if (word == "for" || word == "while" || word == "if" || word == "else")
                            {
                                if (word == "for")
                                {
                                    if (out_flag == 0 || out_flag == 1)
                                    {
                                        cout << "TID: " << tidcount << ", TYPE: " << "8(FOR)" << ", POS: "
                                        << p + k - word.length() + 1 << ", LEN: " << word.length() << ", VALUE: " << word << "\n";
                                        p_flag += 1;
                                    }
                                    tidcount++;
                                    k++;
                                    id_flag = 0;
                                    break;
                                }
                                else if (word == "while")
                                {
                                    if (out_flag == 0 || out_flag == 1)
                                    {
                                        cout << "TID: " << tidcount << ", TYPE: " << "9(WHILE)" << ", POS: "
                                        << p + k - word.length() + 1 << ", LEN: " << word.length() << ", VALUE: " << word << "\n";
                                        p_flag += 1;
                                    }
                                    tidcount++;
                                    k++;
                                    id_flag = 0;
                                    break;
                                }
                                else if (word == "if")
                                {
                                    if (out_flag == 0 || out_flag == 1)
                                    {
                                        cout << "TID: " << tidcount << ", TYPE: " << "10(IF)" << ", POS: "
                                        << p + k - word.length() + 1 << ", LEN: " << word.length() << ", VALUE: " << word << "\n";
                                        p_flag += 1;
                                    }
                                    tidcount++;
                                    k++;
                                    id_flag = 0;
                                    break;
                                }
                                else if (word == "else")
                                {
                                    if (out_flag == 0 || out_flag == 1)
                                    {
                                        cout << "TID: " << tidcount << ", TYPE: " << "11(ELSE)" << ", POS: "
                                        << p + k - word.length() + 1 << ", LEN: " << word.length() << ", VALUE: " << word << "\n";
                                        p_flag += 1;
                                    }
                                    tidcount++;
                                    k++;
                                    id_flag = 0;
                                    break;
                                }
                            }
                            else
                            {
                                k++;
                            }
                        }
                        // flag to skip if it already tokenized for, while, if or else
                        if (id_flag == 1)
                        {
                            // if the bad character is a space
                            if (lines[j][k] == 32)
                            {
                                if (out_flag == 0 || out_flag == 1)
                                {
                                    cout << "TID: " << tidcount << ", TYPE: " << "1(ID)" << ", POS: "
                                    << p + k - word.length() << ", LEN: " << word.length() << ", VALUE: " << word << "\n";
                                    p_flag += 1;
                                }
                                tidcount++;
                                while (lines[j][k] == 32 && k < lines[j].length())
                                {
                                    word += lines[j][k];
                                    k++;
                                }
                                if (out_flag == 0 || out_flag == 2)
                                {
                                    cout << "TID: " << tidcount << ", TYPE: " << "5(WS)" << ", POS: "
                                    << p + k - word.length() << ", LEN: " << word.length() << "\n";
                                    p_flag += 1;
                                }
                                tidcount++;
                            }
                            // if the bad character is a symbol
                            else if ((lines[j][k] >= 33 && lines[j][k] <= 47) || (lines[j][k] >= 58 && lines[j][k] <= 96)
                            || (lines[j][k] >= 123 && lines[j][k] <= 126))
                            {
                                if (out_flag == 0 || out_flag == 1)
                                {
                                    cout << "TID: " << tidcount << ", TYPE: " << "1(ID)" << ", POS: "
                                    << p + k - word.length() << ", LEN: " << word.length() << ", VALUE: " << word << "\n";
                                    p_flag += 1;
                                }
                                tidcount++;
                            }
                            else if (k >= lines[j].length())
                            {
                                if (out_flag == 0 || out_flag == 1)
                                {
                                    cout << "TID: " << tidcount << ", TYPE: " << "1(ID)" << ", POS: "
                                    << p + k - word.length() << ", LEN: " << word.length() << ", VALUE: " << word << "\n";
                                    p_flag += 1;
                                }
                                tidcount++;
                                break;
                            }
                        }
                    }
                    // checking if it's a symbol that's not in the lexical specification at the start meaning a character not valid in the context
                    else if (lines[j][k] == 36 || (lines[j][k] >= 39 && lines[j][k] <= 41) || lines[j][k] == 63 
                    || lines[j][k] == 64 || lines[j][k] == 92 || (lines[j][k] >= 94 && lines[j][k] <= 96) || lines[j][k] == 124 || lines[j][k] == 126)
                    {
                        if (out_flag == 0 || out_flag == 2)
                        {
                            cout << "TID: " << tidcount << ", TYPE: " << "100(ERR4)" << ", POS: "
                            << p + k << ", LEN: " << "1" << "\n";
                            p_flag += 1;
                        }
                        tidcount++;
                        k++;
                    }
                    //checking if it's a symbol in the lexical specification
                    else if (lines[j][k] == 33 || lines[j][k] == 37 || lines[j][k] == 38 || (lines[j][k] >= 42 && lines[j][k] <= 45)
                    || (lines[j][k] >= 47 && lines[j][k] <= 62) || lines[j][k] == 91 || lines[j][k] == 93 || lines[j][k] == 123 || lines[j][k] == 125)
                    {
                        if (lines[j][k] == 60 && lines[j][k + 1] == 61)
                        {
                            word = lines[j][k] + lines[j][k + 1];
                            k++;
                            if (out_flag == 0 || out_flag == 1)
                            {
                                cout << "TID: " << tidcount << ", TYPE: " << "29(<=)" << ", POS: "
                                << p + k - word.length() + 1 << ", LEN: " << "2" << "\n";
                                p_flag += 1;
                            }
                            tidcount++;
                            k++;
                        }
                        else if (lines[j][k] == 62 && lines[j][k + 1] == 61)
                        {
                            word = lines[j][k] + lines[j][k + 1];
                            k++;
                            if (out_flag == 0 || out_flag == 1)
                            {
                                cout << "TID: " << tidcount << ", TYPE: " << "30(>=)" << ", POS: "
                                << p + k - word.length() + 1 << ", LEN: " << "2" << "\n";
                                p_flag += 1;
                            }
                            tidcount++;
                            k++;
                        }
                        else if (lines[j][k] == 33 && lines[j][k + 1] == 61)
                        {
                            word = lines[j][k] + lines[j][k + 1];
                            k++;
                            if (out_flag == 0 || out_flag == 1)
                            {
                                cout << "TID: " << tidcount << ", TYPE: " << "31(!=)" << ", POS: "
                                << p + k - word.length() + 1 << ", LEN: " << "2" << "\n";
                                p_flag += 1;
                            }
                            tidcount++;
                            k++;
                        }
                        else if (lines[j][k] == 58 && lines[j][k + 1] == 61)
                        {
                            word = lines[j][k] + lines[j][k + 1];
                            k++;
                            if (out_flag == 0 || out_flag == 1)
                            {
                                cout << "TID: " << tidcount << ", TYPE: " << "32(:=)" << ", POS: "
                                << p + k - word.length() + 1 << ", LEN: " << "2" << "\n";
                                p_flag += 1;
                            }
                            tidcount++;
                            k++;
                        }
                        else if (lines[j][k] == 58 && lines[j][k + 1] != 61)
                        {
                        	if (out_flag == 0 || out_flag == 2)
                        	{
                            	cout << "TID: " << tidcount << ", TYPE: " << "100(ERR4)" << ", POS: "
                            	<< p + k << ", LEN: " << "1" << "\n";
                            	p_flag += 1;
                       		}
                        	tidcount++;
                        	k++;
                        }
                        else if (lines[j][k] == 33)
                        {
                            if (out_flag == 0 || out_flag == 1)
                            {
                                cout << "TID: " << tidcount << ", TYPE: " << "12(!)" << ", POS: "
                                << p + k << ", LEN: " << "1" << "\n";
                                p_flag += 1;
                            }
                            tidcount++;
                            k++;
                        }
                        else if (lines[j][k] == 37)
                        {
                            if (out_flag == 0 || out_flag == 1)
                            {
                                cout << "TID: " << tidcount << ", TYPE: " << "13(%)" << ", POS: "
                                << p + k << ", LEN: " << "1" << "\n";
                                p_flag += 1;
                            }
                            tidcount++;
                            k++;
                        }
                        else if (lines[j][k] == 38)
                        {
                            if (out_flag == 0 || out_flag == 1)
                            {
                                cout << "TID: " << tidcount << ", TYPE: " << "14(&)" << ", POS: "
                                << p + k << ", LEN: " << "1" << "\n";
                                p_flag += 1;
                            }
                            tidcount++;
                            k++;
                        }
                        else if (lines[j][k] == 42)
                        {
                            if (out_flag == 0 || out_flag == 1)
                            {
                                cout << "TID: " << tidcount << ", TYPE: " << "18(*)" << ", POS: "
                                << p + k << ", LEN: " << "1" << "\n";
                                p_flag += 1;
                            }
                            tidcount++;
                            k++;
                        }
                        else if (lines[j][k] == 43)
                        {
                            if (out_flag == 0 || out_flag == 1)
                            {
                                cout << "TID: " << tidcount << ", TYPE: " << "16(+)" << ", POS: "
                                << p + k << ", LEN: " << "1" << "\n";
                                p_flag += 1;
                            }
                            tidcount++;
                            k++;
                        }
                        else if (lines[j][k] == 44)
                        {
                            if (out_flag == 0 || out_flag == 1)
                            {
                                cout << "TID: " << tidcount << ", TYPE: " << "25(,)" << ", POS: "
                                << p + k << ", LEN: " << "1" << "\n";
                                p_flag += 1;
                            }
                            tidcount++;
                            k++;
                        }
                        else if (lines[j][k] == 45)
                        {
                            if (out_flag == 0 || out_flag == 1)
                            {
                                cout << "TID: " << tidcount << ", TYPE: " << "17(-)" << ", POS: "
                                << p + k << ", LEN: " << "1" << "\n";
                                p_flag += 1;
                            }
                            tidcount++;
                            k++;
                        }
                        else if (lines[j][k] == 47)
                        {
                            if (out_flag == 0 || out_flag == 1)
                            {
                                cout << "TID: " << tidcount << ", TYPE: " << "19(/)" << ", POS: "
                                << p + k << ", LEN: " << "1" << "\n";
                                p_flag += 1;
                            }
                            tidcount++;
                            k++;
                        }
                        else if (lines[j][k] == 59)
                        {
                            if (out_flag == 0 || out_flag == 1)
                            {
                                cout << "TID: " << tidcount << ", TYPE: " << "24(;)" << ", POS: "
                                << p + k << ", LEN: " << "1" << "\n";
                                p_flag += 1;
                            }
                            tidcount++;
                            k++;
                        }
                        else if (lines[j][k] == 60)
                        {
                            if (out_flag == 0 || out_flag == 1)
                            {
                                cout << "TID: " << tidcount << ", TYPE: " << "26(<)" << ", POS: "
                                << p + k << ", LEN: " << "1" << "\n";
                                p_flag += 1;
                            }
                            tidcount++;
                            k++;
                        }
                        else if (lines[j][k] == 61)
                        {
                            if (out_flag == 0 || out_flag == 1)
                            {
                                cout << "TID: " << tidcount << ", TYPE: " << "28(=)" << ", POS: "
                                << p + k << ", LEN: " << "1" << "\n";
                                p_flag += 1;
                            }
                            tidcount++;
                            k++;
                        }
                        else if (lines[j][k] == 62)
                        {
                            if (out_flag == 0 || out_flag == 1)
                            {
                                cout << "TID: " << tidcount << ", TYPE: " << "27(>)" << ", POS: "
                                << p + k << ", LEN: " << "1" << "\n";
                                p_flag += 1;
                            }
                            tidcount++;
                            k++;
                        }
                        else if (lines[j][k] == 91)
                        {
                            if (out_flag == 0 || out_flag == 1)
                            {
                                cout << "TID: " << tidcount << ", TYPE: " << "22([)" << ", POS: "
                                << p + k << ", LEN: " << "1" << "\n";
                                p_flag += 1;
                            }
                            tidcount++;
                            k++;
                        }
                        else if (lines[j][k] == 93)
                        {
                            if (out_flag == 0 || out_flag == 1)
                            {
                                cout << "TID: " << tidcount << ", TYPE: " << "23(])" << ", POS: "
                                << p + k << ", LEN: " << "1" << "\n";
                                p_flag += 1;
                            }
                            tidcount++;
                            k++;
                        }
                        else if (lines[j][k] == 123)
                        {
                            if (out_flag == 0 || out_flag == 1)
                            {
                                cout << "TID: " << tidcount << ", TYPE: " << "20({)" << ", POS: "
                                    << p + k << ", LEN: " << "1" << "\n";
                                    p_flag += 1;
                                }
                                tidcount++;
                                k++;
                            }
                            else if (lines[j][k] == 125)
                            {
                                if (out_flag == 0 || out_flag == 1)
                                {
                                cout << "TID: " << tidcount << ", TYPE: " << "21(})" << ", POS: "
                                << p + k << ", LEN: " << "1" << "\n";
                                p_flag += 1;
                            }
                            tidcount++;
                            k++;
                        }
                    }
                }
                // newline at the end of the line
                if(new_flag != 1)
                {
                	if (out_flag == 0 || out_flag == 2)
		            {
		                cout << "TID: " << tidcount << ", TYPE: " << "6(NEWLINE)" << ", POS: "
		                << p + lines[j].length() << ", LEN: " << "1" << "\n";
		                p_flag += 1;
		            }
                	tidcount++;
                	p += lines[j].length() + 1;
                }
                
            }
            else
            {
                // output the final line
                cout << "\n" << "Totals: " << "len = " << p << ", tokens = " << tidcount - 1 << ", printed = " << p_flag << "\n";
                break;
            }
        }
    }
}
