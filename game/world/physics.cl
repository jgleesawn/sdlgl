float sum( float3 sumee ) {
	return sumee.x+sumee.y+sumee.z;
}
float avg( float v1, float v2) {
	return (v1+v2)/2;
}
//#pragma OPENCL EXTENSION cl_khr_gl_sharing : enable
__kernel void MovementCompute(__constant int * wpos, __constant int * hpos,
			__constant int * w, __constant int * h,
			__constant int * spriteFrame, __global float * movMod,
			__constant int * bgwidth,
			__global int4 * bgTex, __global int4* sTex,
			__local float4 * sum, __global float4 * gsum) { 
	int gid = get_global_id(0);
	if( gid > w[0]*h[0] )
		return;
	int lid = get_local_id(0);
	sum[lid] = 0;

	int curBgPix = (hpos[0] + gid/w[0])*bgwidth[0] + wpos[0] + gid%w[0];
	int curSprPix = gid;
	sum[lid] = convert_float4(abs_diff(bgTex[curBgPix],sTex[curSprPix]));

	barrier(CLK_LOCAL_MEM_FENCE);
	float3 sumd = (float3)(0.0f, 0.0f, 0.0f);
	if( lid == 0 ) {
		for( int i=0; i<get_local_size(0); i++)
			sumd += sum[i].xyz;
		gsum[gid/get_local_size(0)].xyz = sumd;
	}
	barrier(CLK_GLOBAL_MEM_FENCE);
	if( gid ==0 ) {
		sumd = (float3)(0.0f, 0.0f, 0.0f);
		for( int i=0; i<get_global_size(0)/get_local_size(0); i++)
			sumd += gsum[i].xyz;
		float diff = 0;
		diff += sumd.x;
		diff += sumd.y;
		diff += sumd.z;
		diff /= w[0]*h[0]*256*3;
		movMod[0] = diff;
	}
}

