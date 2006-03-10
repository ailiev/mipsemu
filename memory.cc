
status_t mem_init (mem_t * mem,
		   size_t size,
		   size_t textsize)
{
    status_t rc = STATUS_OK;
    
    memset (mem, 0, sizeof(*mem));
    
    mem->size = size;
    
    mem->mem = new byte[size];
    if (mem->mem == NULL) ERREXIT (NOMEM);

    mem->textsize = textsize;
    
 error_egress:

    return rc;
}


status_t mem_write (mem_t * mem,
		    addr_t vaddr, word_t val)
{
    status_t rc = STATUS_OK;
    
    addr_t addr;
    CHECKCALL ( virt2phys_addr (mem, vaddr, &addr) );

    if (addr >= mem->size) ERREXIT(ILLADDR);

    memcpy (mem->mem + addr, &val, sizeof(val));

 error_egress:

    return rc;
}

status_t mem_read (mem_t * mem,
		   addr_t vaddr,
		   word_t * o_val)
{
    status_t rc = STATUS_OK;
    
    addr_t addr;
    CHECKCALL ( virt2phys_addr (mem, vaddr, &addr) );

    if (addr >= mem->size) ERREXIT(ILLADDR);

    memcpy (o_val, mem->mem + addr, sizeof(*o_val));

 error_egress:

    return rc;
}


   
/// convert a full 32-bit address, in MIPS conventions, to an address into one
/// of our compact memory arrays.
status_t virt2phys_addr (const mem_t * mem,
			 addr_t full_addr,
			 addr_t * o_addr)
{
    status_t rc = STATUS_OK;

    if (full_addr < mem_t::TEXT_START ||
	GETBIT(full_addr, mem_t::KERNEL_DETECT_BIT) == 1)
    {
	// too high or too low!
	ERREXIT (ILLADDR);
    }

    
    if (GETBIT(full_addr, mem_t::DATA_DETECT_BIT) == 0)
    {
	// text section
	*o_addr = full_addr - mem_t::TEXT_START;
    }
    else if (GETBIT(full_addr, mem_t::STACK_DETECT_BIT) == 0)
    {
	// data section
	*o_addr = mem->textsize +
	    (full_addr - mem_t::DATA_START); // offset into the data section
    }
    else {
	// stack
	*o_addr = mem->size -
	    (mem_t::STACK_TOP - full_addr); // the offset from top of stack
    }

 error_egress:

    return rc;
}
