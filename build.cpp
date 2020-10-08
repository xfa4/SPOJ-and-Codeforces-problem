#include <sys/stat.h>
#include <bits/stdc++.h>
using namespace std;

const string INP = ".inp";
const string OUT = ".out";

string TASK;
int nTest, nDigit;

bool CheckExistence(string filename) {
    struct stat fileinfo;
    return !stat(filename.c_str(), &fileinfo);
}

string NumToString (int i) {
    string s;
    while (i > 0) {
        s = char (i % 10 + '0') + s;
        i /= 10;
    }
    while (s.size() < nDigit) s = '0' + s;
    return s;
}

void Compile(string File) {
	int exitCode = system (("g++ -std=c++11 -o " + File + " " + File + ".cpp").c_str());
	if (exitCode != 0) {
        cout << "!!!! Error while compiling file: ";
		cout << File << ".cpp\n";
        system ("pause");
		exit (0);
	}
}

void MakeFile(string RunFile, string FileResult, string FileIO, string Folder) {
	int exitCode = system ((".\\" + RunFile + ".exe").c_str());

	if (exitCode != 0) {
        cout << "!!!! Error while runnning file: ";
		cout << RunFile << ".cpp\n";
		cout << "Exit code " << exitCode << '\n';
        system ("pause");
		exit (0);
	}

	system (("cd " + TASK  + "/" + Folder + "&&  type nul > " + FileIO).c_str());
	system (("copy " + FileResult + " " +  TASK  + "\\" + Folder + "\\" + FileIO + " > nul").c_str());
	return;
}

int main() {
    cout << "Enter your problem 's name: "; cin >> TASK;
    cout << "Enter your number of testcases: "; cin >> nTest; cout << "\n";
    nDigit = log10 (nTest) + 1; nDigit = max (2, nDigit);

    Compile ("generate");
    Compile ("solution");

    if (CheckExistence(TASK)) {
        cout << "! Folder " << '"' << TASK << '"' << " existed\n\n";
    } else system (("mkdir " + TASK).c_str());

    for (int iTest = 1; iTest <= nTest; iTest++) {
        string idTest = NumToString (iTest);
        cout << "Test " << idTest << ": ";

        if (CheckExistence (TASK + "\\" + "Test" + idTest)) {
            cout << "! Testcase existed.\n\n";
            continue;
        }

        string Folder = "Test" + idTest;
        system (("cd " + TASK + " && mkdir " + Folder).c_str());

        MakeFile ("generate", TASK + INP, TASK + INP, Folder);
        MakeFile ("solution", TASK + OUT, TASK + OUT, Folder);

        cout << "Complete\n\n";

        if (iTest != nTest) system ("timeout 1 > nul");
    }

    if (CheckExistence((TASK + INP).c_str())) {
        system (("del " + TASK + INP).c_str());
		system (("del " + TASK + OUT).c_str());
	}

	if (CheckExistence("build.o")) system ("del build.o");
	if (CheckExistence("solution.o")) system ("del solution.o");
	if (CheckExistence("generate.o")) system ("del generate.o");
	if (CheckExistence("generate.exe")) system ("del generate.exe");
	if (CheckExistence("solution.exe")) system ("del solution.exe");

    system ("pause");
}
