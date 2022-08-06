clc; 
clear; 
close all;

%% Question1
x1 = -3:0.1:3;
y = myQuantizer(x1,3,1);
figure(1);
stem(x1,y);
title('Characteristic of 3-bit Quantizer');

%% Question2
x = audioread('s3_1.wav');
x_trans = x';

%2.A
xquan1 = myQuantizer(x,3,0.1);
SNR1 = mySNR(x_trans,xquan1);

%2.B
xquan2 = myQuantizer(x,3,max(abs(x)));
SNR2 = mySNR(x_trans,xquan2);

%2.C
xquan3 = myQuantizer(x,3,1);
SNR3 = mySNR(x_trans,xquan3);

%2.D
figure(2);
subplot(3,1,1); 
stem(x,xquan1);
title('Quantization 1');
subplot(3,1,2); 
stem(x,xquan2);
title('Quantization 2');
subplot(3,1,3); 
stem(x,xquan3);
title('Quantization 3');

%2.E
optimum_xm = max(abs(x));
figure(3);
hist = histogram(x);
title('Histogram of Input Signal');

%% Question 3
xquan4 = myQuantizer(x,2,max(abs(x)));
SNR4 = mySNR(x_trans,xquan4);

%% Adaptive Quantizer

xquan5 = myAdaptiveQuantizer(x,3,100);
SNR5 = mySNR(x_trans,xquan5);
figure(4);
subplot(2,1,1); 
stem(x,xquan1);
title('Quantization 2');
subplot(2,1,2); 
stem(x,xquan2);
title('Quantization 5');
