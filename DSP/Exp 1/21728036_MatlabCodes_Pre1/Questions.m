% Egemen Can Ayduðan - 21728036 
% PRELIMINARY WORK 1

close all;
clear all;
clc;

%% Question 2
% 2.a)
[TimeAxis1,x1] = SinSamples(1,2*pi*1000,pi/6,0.002,2*pi*16000);
[FrequencyAxis1,X1]= DFT_Function(x1,2*pi*16000 );

figure(1);
subplot(2,2,[1,2]);
stem(TimeAxis1,x1);
title('Discrete Time Signal of x1'); ylabel("Amplitude"); xlabel("Sample Number");
subplot(2,2,[3,4]);
stem(FrequencyAxis1,X1);
title('Magnitude Spectra of Signal of x1'); ylabel("Amplitude"); xlabel("Sampling Frequency");

% 2.b)
[TimeAxis2,x2] = SinSamples(1,2*pi*1000,0,0.002,2*pi*16000);
[FrequencyAxis2,X2] = DFT_Function(x2 ,2*pi*16000 );

figure(2);
subplot(2,2,[1,2]);
stem(TimeAxis2,x2);
title('Discrete Time Signal of x2'); ylabel("Amplitude"); xlabel("Sample Number");
subplot(2,2,[3,4]);
stem(FrequencyAxis2,X2);
title('Magnitude Spectra of Signal of x2'); ylabel("Amplitude"); xlabel("Sampling Frequency");

%% Question 3
%3.a)
[TimeAxis3,x3] = SinSamples(1,2*pi*1000,0,0.01,2*pi*4000);
[FrequencyAxis3,X3]= DFT_Function(x3,2*pi*4000);

figure(3);
subplot(2,2,[1,2]);
stem(TimeAxis3,x3);
title('Discrete Time Signal of x3'); ylabel("Amplitude"); xlabel("Sample Number");
subplot(2,2,[3,4]);
stem(FrequencyAxis3,X3);
title('Magnitude Spectra of Signal of x3'); ylabel("Amplitude"); xlabel("Sampling Frequency");

%3.b)
[TimeAxis4,x4] = SinSamples(1,2*pi*5000,0,0.01,2*pi*4000);
[FrequencyAxis4,X4] = DFT_Function(x4 ,2*pi*4000 );

figure(4);
subplot(2,2,[1,2]);
stem(TimeAxis4,x4);
title('Discrete Time Signal of x4'); ylabel("Amplitude"); xlabel("Sample Number");
subplot(2,2,[3,4]);
stem(FrequencyAxis4,X4);
title('Magnitude Spectra of Signal of x4'); ylabel("Amplitude"); xlabel("Sampling Frequency");

%% Question 4
%4.a)
[TimeAxis5,x5] = SinSamples(1,2*pi*1000,0,0.0010,2*pi*16000);
[FrequencyAxis5,X5] = DFT_Function(x5,2*pi*16000 );

figure(5);
subplot(2,2,[1,2]);
stem(TimeAxis5,x5);
title('Discrete Time Signal of x5'); ylabel("Amplitude"); xlabel("Sample Number");
subplot(2,2,[3,4]);
stem(FrequencyAxis5,X5);
title('Magnitude Spectra of Signal of x5'); ylabel("Amplitude"); xlabel("Sampling Frequency");

%4.b)
[TimeAxis6,x6] = SinSamples(1,2*pi*1000,0,0.0015,2*pi*16000);
[FrequencyAxis6,X6] = DFT_Function(x6 ,2*pi*16000 );

figure(6);
subplot(2,2,[1,2]);
stem(TimeAxis6,x6);
title('Discrete Time Signal of x6'); ylabel("Amplitude"); xlabel("Sample Number");
subplot(2,2,[3,4]);
stem(FrequencyAxis6,X6);
title('Magnitude Spectra of Signal of x6'); ylabel("Amplitude"); xlabel("Sampling Frequency");

%4.c)
[TimeAxis7,x7] = SinSamples(1,2*pi*1000,0,0.0020,2*pi*16000);
[FrequencyAxis7,X7] = DFT_Function(x7 ,2*pi*16000 );

figure(7);
subplot(2,2,[1,2]);
stem(TimeAxis7,x7);
title('Discrete Time Signal of x7'); ylabel("Amplitude"); xlabel("Sample Number");
subplot(2,2,[3,4]);
stem(FrequencyAxis7,X7);
title('Magnitude Spectra of Signal of x7'); ylabel("Amplitude"); xlabel("Sampling Frequency");

%% Question 5
[TimeAxis8,x8] = SinSamples(3,2*pi*5000,pi/6,2e-3,2*pi*16000);
[FrequencyAxis8,X8] = DFT_Function(x8 ,2*pi*16000 );

xs = x1+x8;
TimeAxisS = TimeAxis8;
[FrequencyAxisS,Xs] = DFT_Function(xs ,2*pi*16000 );


figure(8);

subplot(321);
stem(TimeAxis1,x1);
title('Discrete Time Signal of x1'); ylabel("Amplitude"); xlabel("Sample Number");
subplot(322);
stem(FrequencyAxis1,X1);
title('Magnitude Spectra of Signal of x1'); ylabel("Amplitude"); xlabel("Sampling Frequency");

subplot(323);
stem(TimeAxis8,x8);
title('Discrete Time Signal of x8'); ylabel("Amplitude"); xlabel("Sample Number");
subplot(324);
stem(FrequencyAxis8,X8);
title('Magnitude Spectra of Signal of x8'); ylabel("Amplitude"); xlabel("Sampling Frequency");

subplot(325);
stem(TimeAxisS,xs);
title('Discrete Time Signal of x8'); ylabel("Amplitude"); xlabel("Sample Number");
subplot(326);
stem(FrequencyAxisS,Xs);
title('Magnitude Spectra of xs'); ylabel("Amplitude"); xlabel("Sampling Frequency");

%% Question 6
xm = x8.*x1;
TimeAxisM = TimeAxis8;
[FrequencyAxisM,Xm] = DFT_Function(xm ,2*pi*16000 );

figure(9);
subplot(2,2,[1,2]);
stem(TimeAxisM,xm);
title('Discrete Time Signal of xm'); ylabel("Amplitude"); xlabel("Sample Number");
subplot(2,2,[3,4]);
stem(FrequencyAxisM,Xm);
title('Magnitude Spectra of xm'); ylabel("Amplitude"); xlabel("Sampling Frequency");

%% Question7
% Normal Shifting
x9 = [0,x5(1:end-1)];
[FrequencyAxisX9,X9] = DFT_Function(x9,2*pi*16000);

figure(10);
subplot(2,2,[1,2]);
stem(TimeAxis5,x9);
title('Normal Shift (x(9))'); ylabel("Amplitude"); xlabel("Sample Number");
subplot(2,2,[3,4]);
stem(FrequencyAxisX9,X9);
title('Magnitude Spectra of x9'); ylabel("Amplitude"); xlabel("Sampling Frequency");

% Circular Shifting
x0 = circshift(x5,1);
[FrequencyAxisX0,X0]= DFT_Function(x0,2*pi*16000 );

figure(11);
subplot(2,2,[1,2]);
stem(TimeAxis5,x0);
title('Circular Shift (x(0))'); ylabel("Amplitude"); xlabel("Sample Number");
subplot(2,2,[3,4]);
stem(FrequencyAxisX0,X0);
title('Magnitude Spectra of x0'); ylabel("Amplitude"); xlabel("Sampling Frequency");

%% Question 8
[sound,FsSound] = audioread('sound1.wav');

for n=1 : 512
    Temp2 = sound(n);
    sound512(n) = Temp2; 
end

TimeAxisSound = 0:1/FsSound:(length(sound512)-1)/FsSound;
[FrequencyAxisSound512,Sound512]= DFT_Function(sound512,2*pi*FsSound);

figure(12);
subplot(2,2,[1,2]);
stem(TimeAxisSound,sound512);
title("The Waveform of First 512 Point of Sound"); ylabel('Amplitude'); xlabel('Time'); 
subplot(2,2,[3,4]);
stem(FrequencyAxisSound512,Sound512);
title("The Magnitude Spectra of First 512 Point of Sound"); ylabel("Amplitude"); xlabel("Sampling Frequency");

%% Question 9
for n=0 : 255
    Temp3 = sinc(0.2*(n-128));
    x10(n+1) = Temp3;
end
Norm = 0:1:255;
NormDown = 0:1:127;
[FrequencyAxisX10,X10]= DFT_Function(x10,2*pi*10);

xdown1 = downsample(x10,2);
[FrequencyAxisXdown1,Xdown1] = DFT_Function(xdown1,2*pi*10);

xinterp1 = interp(xdown1,2);
[FrequencyAxisXinterp1,Xinterp1] = DFT_Function(xinterp1,2*pi*10);

figure(13);
subplot(211);
stem(Norm,x10);
title('The Signal x10'); ylabel("Amplitude"); xlabel("Sample Number");
subplot(212);
stem(FrequencyAxisX10,X10);
title('Magnitude Spectra of x10'); ylabel("Amplitude"); xlabel("Sampling Frequency");

figure(14);
subplot(211);
stem(NormDown,xdown1);
title('The Signal xdown1'); ylabel("Amplitude"); xlabel("Sample Number");
subplot(212);
stem(FrequencyAxisXdown1,Xdown1);
title('Magnitude Spectra of xdown1'); ylabel("Amplitude"); xlabel("Sampling Frequency");

figure(15);
subplot(211);
stem(Norm,xinterp1);
title('The Signal xinterp1'); ylabel("Amplitude"); xlabel("Sample Number");
subplot(212);
stem(FrequencyAxisXinterp1,Xinterp1);
title('Magnitude Spectra of xinterp1'); ylabel("Amplitude"); xlabel("Sampling Frequency");

%% Question 10
for n=0 : 255
    Temp4 = sinc(0.8*(n-128));
    x11(n+1) = Temp4;
end
Norm = 0:1:255;
[FrequencyAxisX11,X11]= DFT_Function(x11,2*pi*10);

xdown2 = downsample(x11,2);
[FrequencyAxisXdown2,Xdown2] = DFT_Function(xdown2,2*pi*10);

xinterp2 = interp(xdown2,2);
[FrequencyAxisXinterp2,Xinterp2] = DFT_Function(xinterp2,2*pi*10);

figure(16);
subplot(211);
stem(Norm,x11);
title('The Signal x11'); ylabel("Amplitude"); xlabel("Sample Number");
subplot(212);
stem(FrequencyAxisX11,X11);
title('Magnitude Spectra of x11'); ylabel("Amplitude"); xlabel("Sampling Frequency");

figure(17);
subplot(211);
stem(NormDown,xdown2);
title('The Signal xdown2'); ylabel("Amplitude"); xlabel("Sample Number");
subplot(212);
stem(FrequencyAxisXdown2,Xdown2);
title('Magnitude Spectra of xdown2'); ylabel("Amplitude"); xlabel("Sampling Frequency");

figure(18);
subplot(211);
stem(Norm,xinterp2);
title('The Signal xinterp2'); ylabel("Amplitude"); xlabel("Sample Number");
subplot(212);
stem(FrequencyAxisXinterp2,Xinterp2);
title('Magnitude Spectra of xinterp2'); ylabel("Amplitude"); xlabel("Sampling Frequency");

