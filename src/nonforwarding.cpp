#include "processor.cpp"

using namespace std;

int main(int argc, char const *argv[])
{
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

    for (int i = 0; i < cycle_count; i++)
    {
        vector<int> temp = processor.simulate_clock_cycle_nonforwarding();
        if (temp[0] != -1) {if (i>=1 && (output[temp[0]/4][i-1]=="-" || output[temp[0]/4][i-1] == "IF")) {output[temp[0]/4][i] = "-";} else {output[temp[0]/4][i] = "IF";}}
        if (temp[1] != -1) {if (i>=1 && (output[temp[0]/4][i-1]=="-" || output[temp[1]/4][i-1] == "ID")) {output[temp[1]/4][i] = "-";} else {output[temp[1]/4][i] = "ID";}}
        if (temp[2] != -1) {if (i>=1 && (output[temp[0]/4][i-1]=="-" || output[temp[2]/4][i-1] == "EX")) {output[temp[2]/4][i] = "-";} else {output[temp[2]/4][i] = "EX";}}
        if (temp[3] != -1) {if (i>=1 && (output[temp[0]/4][i-1]=="-" || output[temp[3]/4][i-1] == "MEM")) {output[temp[3]/4][i] = "-";} else {output[temp[3]/4][i] = "MEM";}}
        if (temp[4] != -1) {if (i>=1 && (output[temp[0]/4][i-1]=="-" || output[temp[4]/4][i-1] == "WB")) {output[temp[4]/4][i] = "-";} else {output[temp[4]/4][i] = "WB";}}
    }

    
    ofstream output_file("../outputfiles/"+output_name+"_noforward_out.txt");
    streambuf *cout_buf = cout.rdbuf();
    cout.rdbuf(output_file.rdbuf());

    for (int i = 0; i < insts.size(); i++)
    {
        cout << insts[i][1];
        for (int j = 0; j < cycle_count; j++)
        {
            cout << ";" <<output[i][j];
        }
        cout << endl;
    }
    output_file.close();
    cout.rdbuf(cout_buf);
    return 0;
}
