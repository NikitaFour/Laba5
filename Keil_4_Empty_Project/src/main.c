#include <stm32f10x.h>

void knopka_on(){
	RCC->APB2ENR|=1<<4; 				//Питание на порт C
	GPIOC->CRH&=0xFFFFFFF0;			//Обнуляем и выставляем нужный нам режим
	GPIOC->CRH|=0x00000002;			//general purpose output push pull
	
	RCC->APB2ENR|=1<<2;					//Аналогично для порта А
	GPIOA->CRL&=0xFFFFFFF0;
	GPIOA->CRL|=0x00000004;			//Режим floating input
	while(1){
		if(GPIOA->IDR&1)					//Считываем значение, подаваемое с кнопки
			GPIOC->ODR|=1<<8;				//Выводим на 8 пин высокий уровень
		else
			GPIOC->ODR&=~(1<<8);		//Если на входе 0, то и выводим 0
	}
}

void miganie(){
	RCC->APB2ENR|=1<<4;							//Порт С
	GPIOC->CRH&=0xFFFFFF00; 				//Обнуляем 8 и 9 пины
	GPIOC->CRH|=0x00000022;		 			//Режим general purpose output push pull
	while(1){
		GPIOC->ODR&=~(1<<9);
		GPIOC->ODR|=1<<8;	 						//Подать высокий уровень на 8 пин
		for(int i=0;i<1234567;i++)
		{}
		GPIOC->ODR&=~(1<<8);
		GPIOC->ODR|=1<<9;							//Подать высокий уровень на 9 пин
		for(int i=0;i<1234567;i++)
		{}
	}
}

void vvod_s_klavy(){
	RCC->APB2ENR|=1<<2; 												//Порт A
	GPIOA->CRL&=0x0000000F;
	GPIOA->CRH&=0xFFFFFFF0;											//Обнуляем с 1 по 8 (нулевой не трогаем)
	GPIOA->CRL|=0x22222220;
	GPIOA->CRH|=0x00000002;											//Режим general purpose output push pull
	
	RCC->APB2ENR|=1<<3;													//Порт B
	GPIOB->CRL&=0xFFFFF000;
	GPIOB->CRL|=0x00000444;											//Режим floating input на пинах с 0 по 2 выставляем
	while(1){
		GPIOA->ODR&=0xFFFFFE01;										//Обнуляем порты, чтобы кнопочки гасли
		GPIOA->ODR|=1<<(GPIOB->IDR&7);						//Считываем значения с пинов 0-2 и получаем номер пина cо светодиодом
	}
}

int main()
{
	knopka_on();
	for(int i=0;i<12345678;i++)
		{}
	miganie();
	for(int i=0;i<12345678;i++)
		{}
	vvod_s_klavy();
	for(int i=0;i<12345678;i++)
		{}
	while(1){
	}
	return 0;
}