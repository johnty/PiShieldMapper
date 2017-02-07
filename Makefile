INC_MAP   = /usr/local/include/mapper-0
INC_LO    = /usr/local/include/
INCS      = -I${INC_MAP} -I${INC_LO}

LIB_MAP   = -lmapper-0
LIB_LO    = -llo
LIB_WPI   = -lwiringPi
LIB_DIR   = /usr/local/lib
LDFLAGS   = -L${LIB_DIR} ${LIB_MAP} ${LIB_LO} ${LIB_WPI}


PiShieldMapper: PiShieldMapper.c
	gcc ${INCS} ${LDFLAGS} -Wall -o Demo PiShieldMapper.c 

clean:
	rm Demo
