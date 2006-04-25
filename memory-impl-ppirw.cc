#include "memory-impl.h"

#include "memory.h"

#include <sfdl-runtime/card/array.h>
#include <pir/common/utils.h>
#include <pir/common/sym_crypto.h>
#include <pir/common/openssl_crypto.h>

#include <string.h>

#include <utility>



MIPS_OPEN_NS


const unsigned WORDMASK = sizeof(word_t) - 1;
const unsigned LOG_WORDSIZE = 2;
const size_t WORDSIZE = sizeof(word_t);


#define TRY(code)						\
try {								\
    code							\
}								\
catch (std::exception& ex) {					\
    std::cerr << "Error in " << __func__ << ex.what() << std::endl;	\
    ERREXIT (MEMFAULT);						\
}


struct priv_impl_t {

    pir::Array * ram;

    bool init_done;
};


status_t mem_impl_init (mem_impl_t * mem,
			size_t size)
{
    status_t rc = STATUS_OK;

    priv_impl_t * impl = NULL;

    CHECK_ALLOC ( impl, (priv_impl_t*) malloc (sizeof(priv_impl_t)) );
    
    TRY (
	impl->ram = new pir::Array ("ORAM",
				    std::make_pair (size/WORDSIZE, WORDSIZE),
				    new OpenSSLCryptProvFactory());
	);


    impl->init_done = false;

    mem->size 	   = size;
    mem->priv_impl = impl;

    goto egress;
    
 error_egress:
    if (impl != NULL)
    {
	free (impl);
	mem->priv_impl = NULL;
    }
    
 egress:
    return rc;
}

	
			  

/// Called when the initialization (eg. loading of text and static data) is done
status_t mem_impl_init_complete (mem_impl_t * mem)
{
    status_t rc = STATUS_OK;
    
    priv_impl_t * impl = static_cast<priv_impl_t*> (mem->priv_impl);

    TRY (
	impl->ram->repermute();
	);
    
    impl->init_done = true;

 error_egress:
    return rc;
}


status_t mem_impl_read (mem_impl_t * mem,
			phys_addr_t addr,
			byte * o_buf, size_t num)
{
    status_t rc = STATUS_OK;
    
    priv_impl_t * impl = static_cast<priv_impl_t*> (mem->priv_impl);

    index_t idx;

    byte * buf_ptr = o_buf;

    size_t s, len;

    ByteBuffer buf;
    
    // need to break up the read into a number of word reads, and potentially
    // discard parts of the first and last words

    // start with rounding down to nearest 4
    idx = addr >> LOG_WORDSIZE;

    // read and copy the first (probably only) word
    TRY (
	buf   = impl->ram->read (idx);
	// may discard some of the low or high bytes
	s     = (addr & WORDMASK);
	len   = std::min (WORDSIZE - s, num);
	memcpy (buf_ptr, buf.data() + s, len);
	);

    // now s becomes a count of how many bytes we've written into o_buf
    s = len;
    
    while (s < num)
    {
	buf_ptr += len;
	idx++;

	TRY (
	    buf   = impl->ram->read (idx);
	    );

	len = std::min (WORDSIZE, num - s);
	memcpy (buf_ptr, buf.data(), len);

	s += len;
    }
	
    
 error_egress:
    return rc;
}



status_t mem_impl_write (mem_impl_t * mem,
			 phys_addr_t addr,
			 const byte * bytes, size_t num)
{
    status_t rc = STATUS_OK;
    
    priv_impl_t * impl = static_cast<priv_impl_t*> (mem->priv_impl);

    index_t idx;

    byte * buf_ptr = const_cast<byte*> (bytes);

    size_t s, len;

    
    // need to break up the read into a number of word reads, and potentially
    // discard parts of the first and last words

    // start with rounding down to nearest 4
    idx = addr >> LOG_WORDSIZE;

    s     = (addr & WORDMASK);
    len   = std::min (WORDSIZE - s, num);

    // read and copy the first (probably only) word
    TRY (
	const ByteBuffer first (buf_ptr, len, ByteBuffer::SHALLOW);

	if (impl->init_done) impl->ram->write (idx, s, first);
	else impl->ram->write_clear (idx, s, first);
	);

    // now s becomes a count of how many bytes we've read from 'bytes'
    s = len;
    
    while (s < num)
    {
	buf_ptr += len;
	idx++;

	len = std::min (WORDSIZE, num - s);

	const ByteBuffer buf (buf_ptr, len, ByteBuffer::SHALLOW);
	TRY (
	    if (impl->init_done)    impl->ram->write (idx, 0, buf);
	    else		    impl->ram->write_clear (idx, 0, buf);
	    );

	s += len;
    }
	
    
 error_egress:
    return rc;
    
}


void mem_impl_dump (const mem_impl_t * mem,
		    const std::string& filename)
{
    std::cerr << "PPIR/W memory does not support mem_impl_dump()"
	      << std::endl;
}


CLOSE_NS
