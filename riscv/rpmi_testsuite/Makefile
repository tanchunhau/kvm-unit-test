
# Set VERBOSE to default if not set
ifndef VERBOSE
    VERBOSE=1
endif

tests += $(TEST_DIR)/rpmi_testsuite/platform/sbi_payload/run_test.$(exe)
#tests += $(TEST_DIR)/sieve.$(exe)

#all: $(tests)

# Define the source directories
SRC_DIR_ := $(TEST_DIR)/rpmi_testsuite/platform/sbi_payload
TESTCASE_DIR_ := $(TEST_DIR)/rpmi_testsuite/testcase

# Define the source files using wildcard
SOURCES_ := $(wildcard $(SRC_DIR_)/*.c) \
           $(wildcard $(TESTCASE_DIR_)/*/*.c)

# Create the object file names by replacing .c with .o
cflatobjs += $(patsubst %.c,%.o,$(SOURCES_))

# Prefix the object files with the source directories (dont need)
#cflatobjs += $(addprefix $(SRC_DIR_)/,$(cflatobjs))
#cflatobjs += $(addprefix $(TESTCASE_DIR_)/,$(cflatobjs))
