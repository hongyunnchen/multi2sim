/*
 *  Multi2Sim
 *  Copyright (C) 2015  Rafael Ubal (ubal@ece.neu.edu)
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef ARCH_KEPLER_TIMING_LSU_H
#define ARCH_KEPLER_TIMING_LSU_H

#include "ExecutionUnit.h"

namespace Kepler
{

// Forward declarations
class SM;


/// Class representing the single precision unit of an SM
class LSU : public ExecutionUnit
{
	// Variable number of register read instructions
	std::deque<std::unique_ptr<Uop>> read_buffer;

	// Variable number of submitted memory accesses
	std::deque<std::unique_ptr<Uop>> memory_buffer;

	// Variable number of register write instructions
	std::deque<std::unique_ptr<Uop>> write_buffer;

	// Id in SM
	int id;

public:
	//
	// Static fields
	//

	/// Maximum number of instructions processed per cycle
	static int width;

	/// Size of buffer holding dispatched instructions
	static int dispatch_buffer_size;

	/// Latency of read stage in number of cycles
	static int read_latency;

	/// Size of the read buffer in instructions
	static int read_buffer_size;

	// Maximum number of inflight memory access
	static int max_inflight_mem_accesses;

	/// Latency of write stage in number of cycles
	static int write_latency;

	/// Size of write buffer in instructions
	static int write_buffer_size;

	// Statistics
	long long num_instructions;




	//
	// Class members
	//

	/// Constructor
	LSU(int id, SM *sm) : ExecutionUnit(sm), id(id)
	{
	}

	/// Run the actions occuring in one cycle
	void Run();

	/// Dispatch the given instruction into the LSU
	void Dispatch(std::unique_ptr<Uop> uop) override;

	/// Complete the instruction
	void Complete();

	/// Write stage of the execution pipeline
	void Write();

	/// Memory stage of the execution pipeline
	void Memory();

	/// Read stage of the execution pipeline
	void Read();
};

}

#endif
