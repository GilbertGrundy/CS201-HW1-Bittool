//Gilbert Grundy CS201 HW1

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


//function to convert char array into an unsigned 32bit integer
uint32_t read_arg(char * arg)
{
	char * endptr = arg;
	int64_t value = strtoll(arg, &endptr, 0);
	if(*endptr != '\0')
	{
		fprintf(stderr, "bittool: invalid char in number %s\n", arg);
		exit(-1);
	}

	if(value < 0 || value > UINT32_MAX)
	{
		fprintf(stderr, "bittool: number %s out of range\n", arg);
		exit(-1);
	}

	return(uint32_t) value;
}

//show common bits between the two arguments
void show_bits(char * a1, char * a2)
{
	uint32_t x = read_arg(a1); //argument 1
	uint32_t y = read_arg(a2); //argument 2
	uint32_t z = (x & y); //use the and bitwise operator, to get common bits
	x = z; //save the value, as z will be altered
	uint32_t i = 0;//will be used to record which column the common bits are

	printf("bits: ");

	while(z)
	{
		if(z%2) //if number is odd, found a column
		{
			printf("%u", i); //print current column
			z = z - 1; //take away one, make z even
			if(z) printf(", "); //if z is not zero, print comma
		}

		z = z >> 1; // shift one, effectively divide z by 2
		i++; //record the moving up a column
	}

	printf("\nhex: 0x%X\n", x); //print hex
	printf("signed: %d\n", x); //print signed dec
	printf("unsigned: %u\n", x); //print unsigned dec

	exit(1);
}

//print a 16 bit binary which represents arguments as bit positions
void set_bits(int na, char ** a)
{
	uint32_t x[na]; //array to grab values
	uint32_t final = 0; //final bitwise positions
	uint32_t one = 1; //a 1 to shift

	for(int i = 0; i < na; ++i)
	{	
		x[i] = read_arg(a[i]); //grab value
		if(x[i] > 15) //is value  above 15?
		{		//abort if so.
			fprintf(stderr, "Number greater than 15, too large\n");
			exit(-1);
		}

		final = (final | (one << x[i])); //use bitwise or to grab bit
	}					 //position

	for(int i = 32768; i != 0; i = i/2)
	{
		if(i > final) printf("0"); //if i is greater than final, then 
		else 			   //print zero
		{
			printf("1");
			final = final - i; //if i is less than final, then
		}			   //print 1, and takeaway i from final
	}

	printf("\n\n");

	exit(1);
}

int main(int argc, char **argv)
{
	if(argc < 3) //not enough arguments
	{
		fprintf(stderr, "bittool: usage: bittool <n> <n> [<n> ...]\n");
		return -1;
	}
	if(argc == 3) //two arguments
	{
		show_bits(argv[1], argv[2]);
		return 0;
	}
	//arguments greater than 2
	set_bits(argc - 1, argv + 1);

	return 0;
}
