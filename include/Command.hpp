#ifndef COMMAND_HPP
#define COMMAND_HPP

class Tank;
class Command {
public:
  virtual ~Command() = default;
  virtual void execute(Tank &tank) = 0;
};

#endif
