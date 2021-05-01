"""local_testing_tool.py for Digit Blocks."""

# Usage: `local_testing_tool.py test_number`, where the argument test_number is
# either 0 (Test Set 1), 1 (Test Set 2).

import random
import sys
import time

NUM_CASES = 50
NUM_TOWERS = 20
HEIGHT = 15
S_NUMERATOR = 19131995794056374423098756540547899023413702180946652049981241292126018545306904350366099321347119078652032583488867227895217431806297911694310429334039514156462579697671476886724907447289719647706123340311407317731009795521253453701078446252610184655049627322081301971215320298108283424216000000000000000000000000000
S_DENOMINATOR = 10**300


def GetBoundary(p, q):
  # x >= NUM_CASES * (p / q) * (S_NUMERATOR / S_DENOMINATOR)
  # x >= NUM_CASES * p * S_NUMERATOR / (q * S_DENOMINATOR)
  return (NUM_CASES * p * S_NUMERATOR + q * S_DENOMINATOR - 1) // (
      q * S_DENOMINATOR)


NEED_AT_LEAST = [860939810732536850, 937467793908762347]


class Error(Exception):
  pass


WRONG_NUM_TOKENS_ERROR = (
    "Wrong number of tokens: expected {}, found {}.".format)
NOT_INTEGER_ERROR = "Not an integer: {}.".format
INVALID_LINE_ERROR = "Couldn't read a valid line."
ADDITIONAL_INPUT_ERROR = "Additional input after all cases finish: {}.".format
OUT_OF_BOUNDS_ERROR = "Tower number out of bounds: {}.".format
TOWER_ALREADY_FULL_ERROR = "Tower {} is already full.".format
TOO_SMALL_SUM_ERROR = "Too small sum: {}.".format

INVALID_OUTPUT = "-1"
TOO_SMALL = "-1"
ALL_CORRECT = "1"


def GenerateSeed():
  return int(1e9 * time.time())


def ReadValues(line, num_tokens):
  t = line.split()
  if len(t) != num_tokens:
    raise Error(WRONG_NUM_TOKENS_ERROR(num_tokens, len(t)))
  r = []
  for s in t:
    try:
      v = int(s)
    except:
      raise Error(NOT_INTEGER_ERROR(s[:100]))
    r.append(v)
  return r


def Output(line):
  try:
    print(line)
    sys.stdout.flush()
  except:
    # We ignore errors to avoid giving an error if the contestants' program
    # finishes after writing all required output, but without reading all our
    # responses.
    try:
      sys.stdout.close()
    except:
      pass


def RunCase(input_fn, num_towers, height):
  towers = [""] * num_towers
  for step in range(num_towers * height):
    digit = str(random.randint(0, 9))
    Output(digit)
    try:
      (pos,) = ReadValues(input_fn(), 1)
    except EOFError:
      Output(INVALID_OUTPUT)
      raise Error(INVALID_LINE_ERROR)
    except Error as error:
      Output(INVALID_OUTPUT)
      raise error

    if pos < 1 or pos > num_towers:
      Output(INVALID_OUTPUT)
      raise Error(OUT_OF_BOUNDS_ERROR(pos))
    pos -= 1
    if len(towers[pos]) >= height:
      Output(INVALID_OUTPUT)
      raise Error(TOWER_ALREADY_FULL_ERROR(pos + 1))
    towers[pos] = digit + towers[pos]

  return sum(int(x) for x in towers)


def RunCases(num_cases, num_towers, height, need_correct):

  def Input():
    try:
      return input()
    except EOFError:
      raise
    except:
      raise Error(INVALID_LINE_ERROR)

  Output("{} {} {} {}".format(num_cases, num_towers, height, need_correct))

  total_score = 0
  for case_id in range(num_cases):
    total_score += RunCase(Input, num_towers, height)

  if total_score < need_correct:
    Output(TOO_SMALL)
    raise Error(TOO_SMALL_SUM_ERROR(total_score))
  Output(ALL_CORRECT)

  try:
    extra_input = Input()
    Output(INVALID_OUTPUT)
    raise Error(ADDITIONAL_INPUT_ERROR(extra_input[:100]))
  except EOFError:
    pass


def main():
  assert len(sys.argv) == 2, "Expected 1 argument to local_testing_tool.py"
  index = int(sys.argv[1])
  seed = GenerateSeed()
  random.seed(seed)
  print("Seed: ", seed, file=sys.stderr)
  try:
    try:
      RunCases(NUM_CASES, NUM_TOWERS, HEIGHT, NEED_AT_LEAST[index])
    except Error as error:
      print(error, file=sys.stderr)
      sys.exit(1)
  except Exception as exception:
    # Hopefully this will never happen, but try to finish gracefully
    # and report a judge error in case of unexpected exception.
    Output(INVALID_OUTPUT)
    print("JUDGE_ERROR! Internal judge exception:", file=sys.stderr)
    print(str(type(exception)), file=sys.stderr)
    print(str(exception)[:1000], file=sys.stderr)
    sys.exit(1)


if __name__ == "__main__":
  main()
