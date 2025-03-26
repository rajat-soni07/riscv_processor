#include "processor.cpp"

using namespace std;

int main(int argc, char const *argv[])
{
    string input_path = argv[1]; 
    int cycle_count = atoi(argv[2]);

    // string input_path = "../inputfiles/strlen.txt";
    // int cycle_count = 8;


    int pos = input_path.find_last_of("/");
    string file_name = input_path.substr(pos + 1);
    string output_name = "";

    for (int i = 0; i < file_name.size(); i++)
    {
        if (file_name[i] == '.'){break;}
        output_name += file_name[i];
    }
    

    vector<vector<string>> insts = read_file(input_path);

    Processor processor(insts);
    
    vector<vector<string>> output(insts.size(), vector<string>(cycle_count, "   "));
    vector<int> last(insts.size(), -1);
    string labels[5] = {"IF ", "ID ", "EX ", "MEM", "WB "};

    for (int i = 0; i < cycle_count; i++)
    {
        vector<int> temp = processor.simulate_clock_cycle_nonforwarding();
        for (int j = 0; j < 5; j++)
        {
           
            if (temp[j] != -1) {
                if (j==last[temp[j]/4]){
                    output[temp[j]/4][i] = "-  ";
                }else{
                    output[temp[j]/4][i] = labels[j];
                    last[temp[j]/4] = j;
                }
            }
        }
        
       
    }

    
    ofstream output_file("../outputfiles/"+output_name+"_noforward_out.txt");
    streambuf *cout_buf = cout.rdbuf();
    cout.rdbuf(output_file.rdbuf());
    
    for (int i = 0; i < insts.size(); i++)
    {
        cout << insts[i][1] << string(20 - insts[i][1].size(), ' ');
        for (int j = 0; j < cycle_count; j++)
        {
            cout << "\t;" <<output[i][j];
        }
        cout << endl;
    }
    output_file.close();
    cout.rdbuf(cout_buf);
    return 0;
}
