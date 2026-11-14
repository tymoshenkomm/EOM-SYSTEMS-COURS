#include <stdio.h>
#include <stdint.h>
#include <ctype.h>

void print_binary(uint8_t value)
{
    for (int i = 7; i >= 0; i--) {
        printf("%u", (value >> i) & 1u);
    }
}

void inspect_32bit(uint32_t val32)
{
    uint8_t *bytes = (uint8_t *)&val32;

    printf("\n--- 32-bit Inspection ---\n");
    printf("Value: 0x%08X\n", val32);
    printf("Size:  %zu bytes\n\n", sizeof(val32));

    printf("Memory:\n");
    for (size_t i = 0; i < sizeof(val32); i++) {
        printf("byte %zu (%p): 0x%02X\n", i, (void *)&bytes[i], bytes[i]);
    }

    uint32_t test = 0x12345678;
    uint8_t *test_ptr = (uint8_t *)&test;

    printf("\nByte order: ");
    if (test_ptr[0] == 0x78) {
        printf("Little-endian\n");
    } else if (test_ptr[0] == 0x12) {
        printf("Big-endian\n");
    } else {
        printf("Unknown\n");
    }
}

int main(void)
{
    unsigned int input;
    printf("Enter value (0-255): ");
    if (scanf("%u", &input) != 1 || input > 255) {
        printf("Invalid input! Please enter a number between 0 and 255.\n");
        return 1;
    }

    uint8_t value = (uint8_t)input;

    printf("\nDecimal:      %u\n", value);
    printf("Hexadecimal:  0x%02X\n", value);
    printf("Binary:       ");
    print_binary(value);
    printf("\n");

    if (isprint(value)) {
        printf("Character:    %c\n", value);
    } else {
        printf("Character:    (non-printable)\n");
    }

    inspect_32bit(0x12345678);

    return 0;
}
