#include <algorithm>
#include <iostream>
#include <string>

using std::string;

string cyclePassword(string password, int position) {
  string output;

  if ((position + 4) < password.length()) {
    output.append(password.begin() + position,
                  password.begin() + (position + 4));
  } else {

    output.append(password.begin() + position,
                  password.begin() +
                      (position + (password.length() - position)));

    position = 0;

    output.append(password.begin() + position,
                  password.begin() + (position + (4 - output.length())));
  }

  return output;
}

int main() {
  string pass = cyclePassword("Hello", 3);
  std::cout << pass << std::endl;
}
