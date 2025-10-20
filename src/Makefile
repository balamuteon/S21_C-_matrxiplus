# ==============================================================================
#  CONFIGURATION
# ==============================================================================
CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Werror -I.
GCOV_FLAGS = --coverage
LDFLAGS = -lgtest -lgtest_main -pthread

# ==============================================================================
#  FILES & DIRECTORIES
# ==============================================================================
REPORT_DIR = report
LIB_SOURCES = $(wildcard *.cpp)
TEST_SOURCES = $(wildcard tests/*.cpp)

LIB_OBJS = $(LIB_SOURCES:.cpp=.o)
TEST_OBJS = $(TEST_SOURCES:.cpp=.o)

TARGET_LIB = libs21_matrix_oop.a
TARGET_TEST = test_runner

# ==============================================================================
#  MAIN TARGETS
# ==============================================================================
.PHONY: all test clean gcov_report format leaks

all: $(TARGET_LIB)

test: $(TARGET_TEST)
	./$(TARGET_TEST)

clean:
	rm -f *.o *.a *.gcno *.gcda *.info *.gcov $(TARGET_TEST) tests/*.o tests/*.gcda tests/*.gcno


gcov_report:
	@if [ -d $(REPORT_DIR) ]; then \
		echo "Removing old coverage report directory..."; \
		rm -rf $(REPORT_DIR); \
	fi
	@$(MAKE) CXXFLAGS="$(CXXFLAGS) $(GCOV_FLAGS)" LDFLAGS="$(LDFLAGS) $(GCOV_FLAGS)" test
	@echo "== Generating coverage report... =="
	-lcov --capture --directory . --output-file coverage.info --ignore-errors mismatch,empty
	-lcov --remove coverage.info '/usr/*' '*/tests/*' --output-file coverage.filtered.info
	-genhtml coverage.filtered.info --output-directory $(REPORT_DIR) --ignore-errors empty
	@echo "Coverage report is available at $(REPORT_DIR)/index.html"
	@xdg-open $(REPORT_DIR)/index.html > /dev/null 2>&1 || echo "Could not open browser automatically."
	@$(MAKE) clean

format:
	@if [ ! -f .clang-format ]; then \
		echo "Copying .clang-format file..."; \
		cp ../materials/linters/.clang-format .; \
	fi
	@echo "Checking formatting..."
	clang-format -n $(LIB_SOURCES) $(TEST_SOURCES) *.h
	@echo "Formatting check complete."

leaks: test
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./$(TARGET_TEST)

# ==============================================================================
#  BUILD RULES
# ==============================================================================

$(TARGET_TEST): $(TEST_OBJS) $(TARGET_LIB)
	$(CXX) $(TEST_OBJS) -L. -ls21_matrix_oop $(LDFLAGS) -o $@

$(TARGET_LIB): $(LIB_OBJS)
	ar rcs $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o: tests/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@