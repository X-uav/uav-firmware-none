# src Makefile

include ../Makefile.common

OBJS+=startup.o
#OBJS+=startup_stm32f10x_md.o
OBJS+=main.o
OBJS+=delay.o
OBJS+=led.o
OBJS+=usart.o
OBJS+=iic.o
OBJS+=mpu6050.o
OBJS+=fusion.o
OBJS+=timex.o
OBJS+=pwm.o
OBJS+=control.o
OBJS+=nrf24l01.o
OBJS+=spi.o
OBJS+=bt.o
OBJS+=nvic.o

all: src

src: app.a

app.a: $(OBJS)
		$(AR) cr app.a $(OBJS)
.PHONY: src clean tshow

clean:
		rm -f app.a $(OBJS)
tshow:
		@echo "######################################################################################################"
		@echo "################# optimize settings: $(InfoTextLib), $(InfoTextSrc)"
		@echo "######################################################################################################"
