//values regulated by OF are "amp" for Amplitude, "pan" for Panel
//val1, val2, val3, val4 and val5 are placeholder
//for custom values (e.g. pitch or frequency, delay, decay, feedback)

(
SynthDef(\krach1, {
	arg
	val1= 200, val2 = 4, val3 = 10, val4 = 1, val5 = 35,
	outbus = 0, freq = 200, amp = 0.8, gate = 1, pan = 0, decay = 4;
	var data, env;

	val1 = freq;
	val2 = decay;

	amp = Lag.kr(amp, 0.8);

	// generate, degrade, filter, echo
	data = SinOsc.ar(freq, 0, amp);
	data = Latch.ar(data, Impulse.ar(Rand(val4*100, val5*1000)));
	data = LPF.ar(data, val3*100);
	data = Pan2.ar(data, pan);
	data = data + CombN.ar(data, 0.5, 0.3, 15.0, 0.3, mul:amp);

	// envelope
	env = EnvGen.kr(Env.asr(0.5, 1.0, 1.0), gate: gate, doneAction: decay);
	data = data * env;

	data = [ data[0], data[1] * Select.kr(IRand(0, 3), [ 1, 1, -1 ]) ];

	Out.ar(outbus, data);
	}).store;
)

(
SynthDef(\krach2, {
	arg
	val1 = 0, val2 = 0, val3 = 5, val4 = 20, val5 = 5,
	fdbk = 0.1;
	var in, amp, local, freq, hasFreq, out;
	val1 = fdbk ;
	val2 = freq;
	in = Mix.new(SoundIn.ar([0,1]));
	local = LocalIn.ar(2) + in.dup;
	amp = Amplitude.kr(in, 0.01, 0.01);
	# freq, hasFreq = Pitch.kr(in, ampThreshold: 0.1, median:7);
	out = Mix.new(LFTri.ar(freq*[(val3 / 10), (val4 / 10), 2], 0,LFNoise2.kr((val5 / 10), 0.1, 0.1), amp * 0.1));
4.do({
       local = AllpassN.ar(local, 1, 1, 4)
    });
	LocalOut.ar(local*fdbk);
	Out.ar([0, 1], out )
 }).store;
)

(
SynthDef(\krach3, {
	arg val1 = 10, val2 = 10, val3 = 10, val4 = 33, val5 = 10, val6 = 10, val7 = 17, val8 = 11;

	    Out.ar(0, CombC.ar(Klang.ar(`[[(val1*10),(val1*11),(val2*100),1001]],(val3/10),0)*0.1,val4/100,LFTri.ar((val4/100), 0, (val6/100), 0.11)+LFTri.ar((val7/100), 0, (val8/100), 0.22), 18)!2)
}).store;
)

