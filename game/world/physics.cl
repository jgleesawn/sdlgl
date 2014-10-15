//Much spent on conversion to floats, push conversion of float to division at the end.
float sum( float3 sumee ) {
	return sumee.x+sumee.y+sumee.z;
}
float avg( float v1, float v2) {
	return (v1+v2)/2;
}

const sampler_t sampler = CLK_NORMALIZED_COORDS_FALSE |
CLK_ADDRESS_CLAMP |
CLK_FILTER_NEAREST;

//#pragma OPENCL EXTENSION cl_khr_gl_sharing : enable
__kernel void MovementCompute(__constant int * wpos, __constant int * hpos,
			__constant int * w, __constant int * h,
			__constant int * spriteFrame, __global float * movMod,
			__read_only image2d_t bgTex, __read_only image2d_t sTex,
//			__global int4 * bgTex, __global int4* sTex,
			__local float4 * sum, __global float4 * gsum) { 

	int lid = get_local_id(0)+get_local_id(1)*get_local_size(0);
	sum[lid] = (float4)(0.0,0.0,0.0,1.0);//0);

	int x = get_global_id(0);
	int y = get_global_id(1);	
	int bgx = wpos[0]+x;
	int bgy = hpos[0]+y;


	float4 stp = read_imagef( sTex, sampler, (int2)(spriteFrame[0]*w[0]+x,y) );
	sum[lid] = fabs( stp - read_imagef(bgTex,sampler,(int2)(bgx,bgy)) );
//	sum[lid] = abs_diff( stp, read_imagef(bgTex,sampler,(int2)(bgx,bgy)) );

	if( stp.w != 0 )
		sum[lid].w = 1;
//	else
//		sum[lid] = (float4)(0.0,0.0,0.0,0.0);

	barrier(CLK_LOCAL_MEM_FENCE);
	float4 sumd = (float4)(0.0, 0.0, 0.0, 0.0);
	if( lid == 0 ) {
		for( int i=0; i<get_local_size(0)*get_local_size(1); i++)
			sumd += sum[i];
		gsum[get_group_id(0)+get_group_id(1)*get_num_groups(0)] = sumd;
	}

	barrier(CLK_GLOBAL_MEM_FENCE);
	if( get_global_id(0)+get_global_id(1) ==0 ) {
		sumd = (float4)(0.0, 0.0, 0.0, 0.0);
		for( int i=0; i<get_num_groups(0)*get_num_groups(1); i++)
			sumd += gsum[i];

		float diff = 0;
		diff += sumd.x;
		diff += sumd.y;
		diff += sumd.z;
		diff /= (float)(sumd.w*3);
//		diff *= 2;	//decreases slowdown

		movMod[0] = diff;
	}

}

