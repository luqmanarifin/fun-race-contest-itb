#include <bits/stdc++.h>
#include <dirent.h>

using namespace std;

string folder_name = "bigmod";

bool endsWith(const string& s, const string& suffix)
{
    return s.rfind(suffix) == (s.size()-suffix.size());
}

int main() {
  DIR *dir;
  struct dirent *ent;
  system("mkdir tc/input tc/output");
  if ((dir = opendir ("tc")) != NULL) {
    /* print all the files and directories within directory */
    while ((ent = readdir (dir)) != NULL) {
      string name = ent->d_name;
      if (name == "." || name == ".." || name == "input" || name == "output") {
        continue;
      }
      string oldname = "tc/" + name;
      string newname;
      //cout << name << endl;
      if (endsWith(name, ".in")) {
        int awal = folder_name.size() + 1;
        int len = name.size() - folder_name.size() - 4;
        int num = atoi(name.substr(awal, len).c_str());
        char buffer[300];
        snprintf(buffer, sizeof(buffer), "%d", num);
        newname = "tc/input/input" + (string) buffer + ".txt";
      } else {
        int awal = folder_name.size() + 1;
        int len = name.size() - folder_name.size() - 5;
        int num = atoi(name.substr(awal, len).c_str());
        char buffer[300];
        snprintf(buffer, sizeof(buffer), "%d", num);
        newname = "tc/output/output" + (string) buffer + ".txt";
      }
      cout << oldname << " -> " << newname << endl;
      string query = ("mv " + oldname + " " + newname);
      cout << query << endl;
      system(query.c_str());
    }
    closedir (dir);
  } else {
    /* could not open directory */
    perror ("");
    return EXIT_FAILURE;
  }

  return 0;
}
