function [y] = my_LPF(x,fs,fcut)

filtSpecs = fdesign.lowpass('N,F3db',10,fcut,fs);
lowpass_design = design(filtSpecs,'butter');
y = filter(lowpass_design,x);

end