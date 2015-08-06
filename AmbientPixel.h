#include <StandardCplusplus.h>
#include <system_configuration.h>
#include <unwind-cxx.h>
#include <utility.h>
#include <skInfraredCOM.h>

namespace AmbientPixel
{
	class Pixel
	{
		#define spx_send_port 3
		#define spx_receive_port 2
		#define spx_send_broadcast 255
		skInfraredCOM *ir_port;
		unsigned char device_id;
	public:
		Pixel(unsigned char device_id) {
			this->ir_port = new skInfraredCOM(spx_send_port, spx_receive_port);
			this->device_id = device_id;
		}

		void send(unsigned char data, unsigned char send_to) {
			this->ir_port->Send(send_to, data);
		}

		unsigned char receive() {
			return this->ir_port->Recive(this->device_id);
		}
	};
}
