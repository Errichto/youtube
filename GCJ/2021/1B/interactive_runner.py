# This code can be run as python2 or python3 in most systems.
#
# This is a small program that runs two processes, connecting the stdin of each
# one to the stdout of the other.
# It doesn't perform a lot of checking, so many errors may
# be caught internally by Python (e.g., if your command line has incorrect
# syntax) or not caught at all (e.g., if the judge or solution hangs).
#
# Run this as:
# python interactive_runner.py <cmd_line_judge> -- <cmd_line_solution>
#
# For example, if you have a testing_tool.py in python3 (that takes a single
# integer as a command line parameter) to use as judge -- like one
# downloaded from a problem statement -- and you would run your solution
# in a standalone using one of the following:
#   1. python3 my_solution.py
#   2. ./my_solution
#   3. java Solution
#   4. my_solution.exe
# Then you could run the judge and solution together, using this, as:
#   1. python interactive_runner.py python3 testing_tool.py 0 -- python3 my_solution.py
#   2. python interactive_runner.py python3 testing_tool.py 0 -- ./my_solution
#   3. python interactive_runner.py python3 testing_tool.py 0 -- java solution
#   4. python interactive_runner.py python3 testing_tool.py 0 -- my_solution.exe
# Notice that the solution in cases 2, 3 and 4 would usually have a
# compilation step before running, which you should run in your usual way
# before using this tool.
#
# This is only intended as a convenient tool to help contestants test solutions
# locally. In particular, it is not identical to the implementation on our
# server, which is more complex.
#
# The standard streams are handled the following way:
# - judge's stdin is connected to the solution's stdout;
# - judge's stdout is connected to the solution's stdin;
# - stderrs of both judge and solution are piped to standard error stream, with
#   lines prepended by "judge: " or "sol: " respectively (note, no
#   synchronization is done so it's possible for the messages from both programs
#   to overlap with each other).

from __future__ import print_function
import sys, subprocess, threading

class SubprocessThread(threading.Thread):
  def __init__(self,
               args,
               stdin_pipe=subprocess.PIPE,
               stdout_pipe=subprocess.PIPE,
               stderr_prefix=None):
    threading.Thread.__init__(self)
    self.stderr_prefix = stderr_prefix
    self.p = subprocess.Popen(
        args, stdin=stdin_pipe, stdout=stdout_pipe, stderr=subprocess.PIPE)

  def run(self):
    try:
      self.pipeToStdErr(self.p.stderr)
      self.return_code = self.p.wait()
      self.error_message = None
    except (SystemError, OSError):
      self.return_code = -1
      self.error_message = "The process crashed or produced too much output."

  # Reads bytes from the stream and writes them to sys.stderr prepending lines
  # with self.stderr_prefix.
  # We are not reading by lines to guard against the case when EOL is never
  # found in the stream.
  def pipeToStdErr(self, stream):
    new_line = True
    while True:
      chunk = stream.readline(1024)
      if not chunk:
        return
      chunk = chunk.decode("UTF-8")
      if new_line and self.stderr_prefix:
        chunk = self.stderr_prefix + chunk
        new_line = False
      sys.stderr.write(chunk)
      if chunk.endswith("\n"):
        new_line = True
      sys.stderr.flush()


assert sys.argv.count("--") == 1, (
    "There should be exactly one instance of '--' in the command line.")
sep_index = sys.argv.index("--")
judge_args = sys.argv[1:sep_index]
sol_args = sys.argv[sep_index + 1:]

t_sol = SubprocessThread(sol_args, stderr_prefix="  sol: ")
t_judge = SubprocessThread(
    judge_args,
    stdin_pipe=t_sol.p.stdout,
    stdout_pipe=t_sol.p.stdin,
    stderr_prefix="judge: ")
t_sol.start()
t_judge.start()
t_sol.join()
t_judge.join()

# Print an empty line to handle the case when stderr doesn't print EOL.
print()
print("Judge return code:", t_judge.return_code)
if t_judge.error_message:
  print("Judge error message:", t_judge.error_message)

print("Solution return code:", t_sol.return_code)
if t_sol.error_message:
  print("Solution error message:", t_sol.error_message)

if t_sol.return_code:
  print("A solution finishing with exit code other than 0 (without exceeding "
        "time or memory limits) would be interpreted as a Runtime Error "
        "in the system.")
elif t_judge.return_code:
  print("A solution finishing with exit code 0 (without exceeding time or "
        "memory limits) and a judge finishing with exit code other than 0 "
        "would be interpreted as a Wrong Answer in the system.")
else:
  print("A solution and judge both finishing with exit code 0 (without "
        "exceeding time or memory limits) would be interpreted as Correct "
        "in the system.")
