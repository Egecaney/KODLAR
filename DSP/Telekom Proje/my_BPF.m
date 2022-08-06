function [y] = my_BPF(x,fs,fclo,fchi)

filtSpecs = fdesign.bandpass('N,F3db1,F3db2',10,fclo,fchi,fs);
bandpass_filter = design(filtSpecs,'butter');
y = filter(bandpass_filter,x);

end