float sum( float3 sumee ) {
	return sumee.x+sumee.y+sumee.z;
}
float avg( float v1, float v2) {
	return (v1+v2)/2;
}
//#pragma OPENCL EXTENSION cl_khr_gl_sharing : enable
__kernel void pixelInteract(__constant int * widthp, __constant int * heightp, 
			__global float4* vals) {
	int gid = get_global_id(0);
	float4 pixel = vals[gid];
	int width,height,w,h;
	width = widthp[0];
	height = heightp[0];
//	if( gid >= width*height )
//		return;
	w = gid % width;
	h = gid / width;

//	vals[gid] /= 2;
	if( sum(pixel.xyz) > 256*2 ) {
		float min = 256;
		int pos = 0;
		int minp = 0;
		if( h > 0 ) {
			pos = gid - width;
			if( sum(vals[pos].xyz) < min )
				minp = pos;
		}
		if( h < height ) {
			pos = gid + width;
			if( sum(vals[pos].xyz) < min )
				minp = pos;
		}
		if( w > 0 ) {
			pos = gid - 1;
			if( sum(vals[pos].xyz) < min )
				minp = pos;
		}
		if( w < width ) {
			pos = gid + 1;
			if( sum(vals[pos].xyz) < min )
				minp = pos;
		}
		int i;
		float4 cval = vals[pos];
		pixel.x = avg(pixel.x, cval.x);
		pixel.y = avg(pixel.y, cval.y);
		pixel.z = avg(pixel.z, cval.z);

		vals[gid] = pixel;
		vals[pos] = (float4)(pixel.xyz,cval.w);
	}
}


__kernel void updateVelocity(__constant float4 * curPos, __global float4* positions,
			__local float4* force, __global float4* velocities,
			__constant int * curInd, __global float4* commBuff ) {
	float3 diff,sum;
	float len,c1,c2;
	float m1,m2;

	float4 cpos = positions[curInd[0]]; //curPos[0];
	float4 cvel = velocities[curInd[0]];
	float4 d,p; //position, momentum
	
	int global_id = get_global_id(0);
	int local_id = get_local_id(0);
	int work_id = global_id/get_local_size(0);

if( global_id != curInd[0] ) {
	d = positions[global_id];
	p = velocities[global_id];
	c1 = cpos.w;
	c2 = d.w;

	m1 = cvel.w;
	m2 = p.w;

	diff = d.xyz - cpos.xyz;
	len = length(diff);
	len *= 1000;		//scales distance
	
	//float dist = 0.45f;
	float dist = 0.45f;
	dist = 0.1f;
	if( len < dist )
		len = dist;
	float G = 0.00000001f*1.0f;	//charge/mass ratio of 10^8
	float K = 1.0f;		//coloumbar constant.  using <1 to simulate higher gravity.
	len = len*len;
	sum  = -K*c1*c2* diff/len;	//Charge based.
	sum +=  G*m1*m2* diff/len;	//Mass based.(gravity)

//Influence of terms changes at len = 1;
	len = len*len;
//	if( c1 >= 0 && c2 >= 0 )
//		sum += sum + c1*c2*(diff/len);
} else {
	sum = (float3)(0.0f, 0.0f, 0.0f);
}

	force[local_id] = (float4)(sum,0.0f);

	barrier(CLK_LOCAL_MEM_FENCE);
	
	if(local_id == 0) {
		sum = (float3)(0.0f, 0.0f, 0.0f);
		for(int i=0; i<get_local_size(0); i++)
			sum += force[i].xyz;
		commBuff[work_id].xyz = sum;
	}
	
	barrier(CLK_GLOBAL_MEM_FENCE);
	if(global_id == 0) {
		sum = (float3)(0.0f, 0.0f, 0.0f);
		for(int i=0; i<(get_global_size(0)/get_local_size(0)); i++) {
			sum += commBuff[i].xyz;
		}
		//Adds force to velocity as acceleration.
		int ci = curInd[0];
		float mass = velocities[ci].w;
		if( mass < 0.001 ) { mass = 0.001; }
		velocities[ci].xyz += sum/(mass*1);//*100 is timestep.
	}
}
/*
*/

__kernel void applyVelocity(__global float4* positions, __global float4* velocities) {
	int gi = get_global_id(0);
//	velocities[gi].xyz *= 0.5f;
	float3 pos = positions[gi].xyz;
//	if( length(pos) < 20 ) {
		pos += velocities[gi].xyz;
//	}
	positions[gi].xyz = pos;
}
/*
*/
