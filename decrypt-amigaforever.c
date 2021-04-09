/* 
 * Copyright (c) 2018 Barry Nelson.
 * 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 2.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * See <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	char *pname;
	int keyfd,romfd;
	ssize_t nromchars, nkeychars;
	unsigned short romchar,keychar;
	char rombuff[12];

	pname=strrchr(argv[0], '/');
	if (pname==NULL)
		pname=argv[0];
	else
		pname++;
	if (argc<2)
	{
		fprintf(stderr,"Usage: %s rom_file_name >output_file\n",pname);
		exit(1);
	}
	keyfd=open("rom.key", O_RDONLY);
	if (keyfd<0)
	{
		fprintf(stderr,"Failed to open \"rom.key\": %s\n",strerror(errno));
		exit(errno);
	}
	romfd=open(argv[1], O_RDONLY);
	if (romfd<0)
	{
		fprintf(stderr,"Failed to open \"%s\": %s\n",argv[1],strerror(errno));
		exit(errno);
	}
	nromchars=read(romfd, rombuff, 11);
	rombuff[11]='\0';
	if (nromchars!=11 || strcmp(rombuff,"AMIROMTYPE1")!=0)
	{
		fprintf(stderr,"The file \"%s\" is not a AMIROMTYPE1 encrypted file.\n",argv[1]);
		exit(1);
	}
	while ((nromchars=read(romfd, &romchar, 1))>0)
	{
		nkeychars=read(keyfd, &keychar, 1);
		if (nkeychars<=0)
		{
			lseek(keyfd, 0L, SEEK_SET);
			read(keyfd, &keychar, 1);
		}
		putchar(romchar ^ keychar);
	}
}
