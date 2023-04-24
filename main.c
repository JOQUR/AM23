#include <stdio.h>
#include "amcom_unit_test.h"

int main()
{
    printf("Running AMCOM unit test...\n");
    if (true == AMCOM_UnitTest()) {
        printf("---------------------------\n");
        printf("      !!! SUCCESS !!!\n");
        printf("---------------------------\n");
		return 0;
	}
	
    printf("---------------------------\n");
    printf("        TEST FAILED\n");
    printf("---------------------------\n");
	return 1;
}