#include "processor.cpp"

using namespace std;

#ifndef MODE
#define MODE 0
#endif

int main(int argc, char const *argv[])
{
    // mode 0 means non forwarding - that is by default if no compile time flags are set
    int mode = 0;

    #if MODE == 0
        mode = 0;
    #endif
    #if MODE == 1
        mode = 1;
    #endif

    // This is taking the inputs from command line
    string input_path = argv[1]; 
    int cycle_count = atoi(argv[2]);


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
    
    vector<vector<string>> output(insts.size(), vector<string>(cycle_count, ""));
    vector<int> last(insts.size(), -1);

    int max_len = 0;
    int max_len_inst = 0;

    for (int i = 0; i < insts.size(); i++)
    {
        max_len_inst = max(max_len_inst, (int)insts[i][1].size());
    }

    string labels[5] = {"IF", "ID", "EX", "MEM", "WB"};

    for (int i = 0; i < cycle_count; i++)
    {
        vector<int> temp;
        if (mode==1){
        temp = processor.simulate_clock_cycle_forwarding();
        }
        else{
        temp = processor.simulate_clock_cycle_nonforwarding();
        }

        if (temp[0]==-1 && temp[1]==-1 && temp[2]==-1 && temp[3]==-1 && temp[4]==-1){
            cycle_count = i;
            break;
        }
        // cout<<temp[0]<<" "<<temp[1]<<" "<<temp[2]<<" "<<temp[3]<<" "<<temp[4]<<endl;
        for (int j = 0; j < 5; j++)
        {
            
            if (temp[j] != -1) {
                if (j==last[temp[j]/4]){
                    output[temp[j]/4][i] = "-";
                }else{
                    if (output[temp[j]/4][i] != ""){
                        output[temp[j]/4][i] += "/";
                    }
                    output[temp[j]/4][i] += labels[j];
                    max_len = max(max_len, (int)output[temp[j]/4][i].size());
                    last[temp[j]/4] = j;
                }
            }
            
        }
        
       
    }

    string suffix;
    if( mode==1){
    suffix = "_forward_out.txt";}
    else
    {
    suffix = "_noforward_out.txt";
    }

    ofstream output_file("../outputfiles/"+output_name+suffix);
    streambuf *cout_buf = cout.rdbuf();
    cout.rdbuf(output_file.rdbuf());
    
    cout  << string(max_len_inst +1, ' ');
    for (int i = 0; i < cycle_count; i++)
    {
        cout << "; " << i << string(max_len + 1 - to_string(i).size(), ' ');
    }
    cout << endl;

    for (int i = 0; i < insts.size(); i++)
    {
        cout << insts[i][1] << string(max_len_inst + 1 - insts[i][1].size(), ' ');
        for (int j = 0; j < cycle_count; j++)
        {
            cout << "; " <<output[i][j] <<string(max_len +1 - output[i][j].size(), ' ');
        }
        cout << endl;
    }
    output_file.close();
    cout.rdbuf(cout_buf);
    return 0;
}
