s.boot;
s.makeWindow;
//values regulated by OF are "amp" for Amplitude, "pan" for Panel
//val1, val2, val3, val4 and val5 are placeholder
//for custom values (e.g. pitch or frequency, delay, decay, feedback)

(
SynthDef(\krach1, {
	arg outbus = 0, freq = 400, amp = 0.1, gate = 1, pan = 0, inbus = 0, wet = 0.5, delaytime = 0.5, decaytime = 2.0, fade = 0.7, decay = 4, val1= 5, val2 = 4, val3 = 10, val4 = 10, val5 = 35;
	var data, env, in, out;

	val1 = freq;
	val2 = decay;
	amp = Lag.kr(amp, 0.4);
	in = In.ar(inbus, 2);

	data = LFPulse.ar(freq, 0, amp);
	data = Latch.ar(data, Impulse.ar(Rand(val4*100), (val5*1000)));
	data = LPF.ar(data, (val3*100));
	data = Pan2.ar(data, pan);
	data = data + CombN.ar(data, 0.5, 0.3, 15.0, 0.3);
	env = EnvGen.kr(Env.asr(0.5, 1.0, 1.0), gate: gate, doneAction: decay);
	data = data * env;
	data = [ data[0], data[1] * Select.kr(IRand(0, 3), [ 1, 1, -1 ]) ];

	out = Mix.new([ data, CombN.ar(in, 2.0, delaytime, decaytime, mul:amp)]);
	out = (wet * out) + ((1 - wet) * in);
	out = Pan2.ar(out, pan);
	Out.ar(outbus, out);
}).store;

SynthDef(\krach2, {
	arg
	val1 = 0, val2 = 0, val3 = 5, val4 = 20, val5 = 5, pan=0, amp = 0.1, fdbk = 0.1;
	var in, ampVal, local, freq, hasFreq, out;
	val1 = fdbk ;
	in = Mix.new(SoundIn.ar([0,1]));
	local = LocalIn.ar(2) + in.dup;
	ampVal = Amplitude.kr(in, 0.01, 0.01);
	# freq, hasFreq = Pitch.kr(in, ampThreshold: 0.1, median:7);
	out = Mix.new(LFTri.ar(freq*[(val3 / 10), (val4 / 10), 2], 0,LFNoise2.kr((val5 / 10), 0.1, 0.1), ampVal * amp));

4.do({
       local = AllpassN.ar(local, 1, 1, 4)
    });
	LocalOut.ar(local*fdbk);
	Out.ar([0, 1], out )
 }).store;

SynthDef(\krach3, {
	arg val1 = 10, val2 = 10, val3 = 10, val4 = 33, val5 = 10, val6 = 10, val7 = 17, val8 = 11, amp = 0.8, pan = -1;
	var out;
	out = Mix.new(CombC.ar(Klang.ar(`[[(val1*10),(val1*11),(val2*100),1001]],(val3/10),0)*0.1,val4/100,LFTri.ar((val4/100), 0, (val6/100), 0.11)+LFTri.ar((val7/100), 0, (val8/100), 0.22), 18, mul:amp));
	out = Pan2.ar(out, -1);
	Out.ar([0, 1], out );
}).store;
)

