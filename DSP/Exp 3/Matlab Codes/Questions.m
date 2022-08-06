clc;
clear all;

% Egemen Can Ayduðan - 21728036
% PRELIMINARY WORK 3

%% Question 1
[TimeAxis1,Xdiscrete1] = SinSamples(3,2*pi,0,2,100*pi);

%1.A
Quantized1 = Midrise_Quantizer(Xdiscrete1,3);
Error_1A = Xdiscrete1-Quantized1;
SNR_1A = 10*log10(var(Xdiscrete1)/var(Error_1A)); 

figure(1);
subplot(3,1,1);
stem(TimeAxis1,Xdiscrete1);
title('Original Signal'); xlabel('Sample Number'); ylabel('Amplitude');
subplot(3,1,2);
plot(TimeAxis1,Quantized1);
title('Midrise Quantized Signal'); xlabel('Sample Number'); ylabel('Amplitude');
subplot(3,1,3);
stem(TimeAxis1,Error_1A);
title('Error Between Original Signal and Midrise Quantized Signal'); xlabel('Sample Number'); ylabel('Amplitude');

%1.B
Quantized2 = Midtread_Quantizer(Xdiscrete1,3);
Error_1B = Xdiscrete1-Quantized2;
SNR_1B = 10*log10(var(Xdiscrete1)/var(Error_1B));

figure(2);
subplot(3,1,1);
stem(TimeAxis1,Xdiscrete1);
title('Original Signal'); xlabel('Sample Number'); ylabel('Amplitude');
subplot(3,1,2);
plot(TimeAxis1,Quantized2);
title('Midtread Quantized Signal'); xlabel('Sample Number'); ylabel('Amplitude');
subplot(3,1,3);
stem(TimeAxis1,Error_1B);
title('Error Between Original Signal and Midtread Quantized Signal'); xlabel('Sample Number'); ylabel('Amplitude');

%% Question 2
% x1[n] = 0.5x[n]
Xdiscrete2 = 0.5*Xdiscrete1;
Quantized3 = Midrise_Quantizer(Xdiscrete2,3);
Error_2A = Xdiscrete2-Quantized3;
SNR_2A = 10*log10(var(Xdiscrete2)/var(Error_2A));

figure(3);
subplot(3,1,1);
stem(TimeAxis1,Xdiscrete2);
title('Original Signal(x_1[n])'); xlabel('Sample Number'); ylabel('Amplitude');
subplot(3,1,2);
plot(TimeAxis1,Quantized3);
title('Midrise Quantized Signal'); xlabel('Sample Number'); ylabel('Amplitude');
subplot(3,1,3);
stem(TimeAxis1,Error_2A);
title('Error Between Original Signal and Midrise Quantized Signal'); xlabel('Sample Number'); ylabel('Amplitude');

% x2[n] = 2x[n]
Xdiscrete3 = 2*Xdiscrete1;
Quantized4 = Midrise_Quantizer(Xdiscrete3,3);
Error_2B = Xdiscrete3-Quantized4;
SNR_2B = 10*log10(var(Xdiscrete3)/var(Error_2B));

figure(4);
subplot(3,1,1);
stem(TimeAxis1,Xdiscrete3);
title('Original Signal(x_2[n])'); xlabel('Sample Number'); ylabel('Amplitude');
subplot(3,1,2);
plot(TimeAxis1,Quantized4);
title('Midrise Quantized Signal'); xlabel('Sample Number'); ylabel('Amplitude');
subplot(3,1,3);
stem(TimeAxis1,Error_2B);
title('Error Between Original Signal and Midrise Quantized Signal'); xlabel('Sample Number'); ylabel('Amplitude');

%% Question 3
[Sound3,FsSound3] = audioread('sound3.wav');
Quantized5 = Midrise_Quantizer(Sound3,3); 
Error3 = Sound3'-Quantized5;
SNR_3 = 10*log10(var(Sound3)./var(Error3));

% sound(Sound3);
% sound(Quantized5);

figure(5);
subplot(2,1,1);
plot(Quantized5);
title('Encoded Version (3 Bits)'); xlabel('Sample Number'); ylabel('Amplitude');
subplot(2,1,2);
plot(Error3);
title('Error Between Original Signal and Encoded Version'); xlabel('Sample Number'); ylabel('Amplitude');

%% Question 4
Quantized6 = Midrise_Quantizer(Sound3,4); 
Error4 = Sound3'-Quantized6;
SNR_4 = 10*log10(var(Sound3)./var(Error4));

% sound(Sound4);
% sound(Quantized6);

figure(6);
subplot(2,1,1);
plot(Quantized6);
title('Encoded Version (4 Bits)'); xlabel('Sample Number'); ylabel('Amplitude');
subplot(2,1,2);
plot(Error4);
title('Error Between Original Signal and Encoded Version'); xlabel('Sample Number'); ylabel('Amplitude');

%% Question 5
N = 100;
Nmax = length(Sound3)/N;
Z = linspace(1,N);
First = reshape(Sound3,N,[]);
for i=1:Nmax
    temp = 1;
    for k=1:100
        Second(temp) = First(temp,i)
        temp = temp+1;
    end
    Quantized7(Z) = Midrise_Quantizer(Second,3);
    Z = Z+100;
end

% sound(Sound3)
% sound(Quantized7)

Error5 = Sound3'-Quantized7;
SNR_5 = 10*log10(var(Sound3)/var(Error5));

figure(7);
subplot(3,1,1);
plot(Sound3);
title('Original Signal of Sound3'); xlabel('Time'); ylabel('Amplitude');
subplot(3,1,2);
plot(Quantized7);
title('Encoded Version - Segmentation (3 Bits)'); ylabel('Amplitude');
subplot(3,1,3);
plot(Error5);
title('Error Between Original Signal and Encoded Version'); xlabel('Sample Number'); ylabel('Amplitude');
