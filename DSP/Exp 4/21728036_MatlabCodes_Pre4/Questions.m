% PRELIMINARY WORK 4
% Egemen Can Ayduðan - 21728036

%% Question 1
[x_input,Fs] = audioread('sound4.wav');

X_input = fftshift(abs(fft(x_input)));
FrequencyAxisXinput = (-Fs/2):(Fs/length(x_input)):(Fs/2)-(Fs/length(x_input));

figure(1);
subplot(2,1,1); 
plot(x_input); 
title('Input Waveform (sound4.wav)'); ylabel('Magnitude'); xlabel('Time(s)');
subplot(2,1,2);
plot(FrequencyAxisXinput,X_input); 
title('Magnitude Spectrum (sound4.wav)'); ylabel('Magnitude'); xlabel('Frequency (Hz)');
% Peak Frequencies of Sound4: 0Hz, 381.2Hz, 762.3Hz, 1147Hz, 2306Hz

%% Question 3
% First dominant peak is at 381.2 Hz
% Rp = 1 , wp = 375 Hz , Rs = 80 and ws = 400 Hz

%% Question 5
xChebyshev1_4 = filter(Chebyshev1_4,x_input);  
xChebyshev2_4 = filter(Chebyshev2_4,x_input); 
xButterworth_4 = filter(Butterworth_4,x_input);

XChebyshev1_4 = fftshift(abs(fft(xChebyshev1_4))); 
XChebyshev2_4 = fftshift(abs(fft(xChebyshev2_4))); 
XButterworth_4 = fftshift(abs(fft(xButterworth_4)));

figure(2); 
subplot(2,1,1); 
plot(xChebyshev1_4); 
title('Output Signal (Chebyshev I)'); ylabel('Magnitude');
subplot(2,1,2); 
plot(FrequencyAxisXinput,XChebyshev1_4); 
title('Magnitude Spectrum of Output Signal (Chebyshev I)'); xlabel('Frequency (Hz)'); ylabel('Magnitude'); 

figure(3);
subplot(2,1,1); 
plot(xChebyshev2_4); 
title('Output Signal (Chebyshev II)'); ylabel('Magnitude'); 
subplot(2,1,2); 
plot(FrequencyAxisXinput,XChebyshev2_4); 
title('Magnitude Spectrum of Output Signal (Chebyshev II)'); xlabel('Frequency (Hz)'); ylabel('Magnitude');

figure(4);
subplot(2,1,1); 
plot(xButterworth_4); 
title('Output Signal (Butterworth)'); ylabel('Magnitude');
subplot(2,1,2); 
plot(FrequencyAxisXinput,XButterworth_4); 
title('Magnitude Spectrum of Output Signal (Butterworth)'); xlabel('Frequency (Hz)'); ylabel('Magnitude');

%% Question 6
% Second dominant peak is at 762.3 Hz
% Fstop1 = 700 Hz, Fpass1 = 750 Hz, Fpass2 = 800 Hz, Fstop2 = 850 Hz

%% Question 8
xChebyshev1_Bandpass = filter(Chebyshev1_7,x_input); 
xChebyshev2_Bandpass = filter(Chebyshev2_7,x_input); 
xButterworth_Bandpass = filter(Butterworth_7,x_input);

XChebyshev1_Bandpass = fftshift(abs(fft(xChebyshev1_Bandpass))); 
XChebyshev2_Bandpass = fftshift(abs(fft(xChebyshev2_Bandpass))); 
XButterworth_Bandpass = fftshift(abs(fft(xButterworth_Bandpass)));

figure(5); 
subplot(2,1,1); 
plot(xChebyshev1_Bandpass); 
title('Output Signal (Chebyshev I)'); ylabel('Magnitude');
subplot(2,1,2); 
plot(FrequencyAxisXinput,XChebyshev1_Bandpass); 
title('Magnitude Spectrum of Output Signal (Chebyshev I)'); xlabel('Frequency (Hz)'); ylabel('Magnitude'); 

figure(6);
subplot(2,1,1); 
plot(xChebyshev2_Bandpass); 
title('Output Signal (Chebyshev II)'); ylabel('Magnitude'); 
subplot(2,1,2); 
plot(FrequencyAxisXinput,XChebyshev2_Bandpass); 
title('Magnitude Spectrum of Output Signal (Chebyshev II)'); xlabel('Frequency (Hz)'); ylabel('Magnitude');

figure(7);
subplot(2,1,1); 
plot(xButterworth_Bandpass); 
title('Output Signal (Butterworth)'); ylabel('Magnitude');
subplot(2,1,2); 
plot(FrequencyAxisXinput,XButterworth_Bandpass); 
title('Magnitude Spectrum of Output Signal (Butterworth)'); xlabel('Frequency (Hz)'); ylabel('Magnitude');

%% Question 10
[input_bana,Fs_bana] = audioread('bana.wav');
Input_Bana = fftshift(abs(fft(input_bana)));

N = length(Input_Bana); 
F = Fs_bana/N;
TimeAxisBana = (1:N)/Fs_bana; 
FreqAxisBana = linspace(-Fs_bana/2,Fs_bana/2-F,N);

filtered_bana = filter(FilterBana,input_bana); 
Filtered_Bana = fftshift(abs(fft(filtered_bana)));

% sound(input_bana);
% sound(filtered_bana);

figure(8); 
subplot(2,2,1); 
plot(TimeAxisBana,input_bana); 
title('Original Signal'); xlabel('Time (sec)'); ylabel('Magnitude'); 
subplot(2,2,2); 
plot(FreqAxisBana,Input_Bana); 
title('Magnitude Spectrum (Original)'); xlabel('Frequency (Hz)'); ylabel('Magnitude'); 
subplot(2,2,3); 
plot(TimeAxisBana,filtered_bana); 
title('Filtered Signal'); xlabel('Time (sec)'); ylabel('Magnitude'); 
subplot(2,2,4); 
plot(FreqAxisBana,Filtered_Bana); 
title('Magnitude Spectrum (Filtered)'); xlabel('Frequency (Hz)'); ylabel('Magnitude');



