/*************************************************************
 * This file was automatically generated on 2011-09-20.      *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generator git on tinkerforge.com                   *
 *************************************************************/

namespace Tinkerforge
{
	public class BrickletIO4 : Device 
	{
		private static byte TYPE_SET_VALUE = 1;
		private static byte TYPE_GET_VALUE = 2;
		private static byte TYPE_SET_CONFIGURATION = 3;
		private static byte TYPE_GET_CONFIGURATION = 4;
		private static byte TYPE_SET_DEBOUNCE_PERIOD = 5;
		private static byte TYPE_GET_DEBOUNCE_PERIOD = 6;
		private static byte TYPE_SET_INTERRUPT = 7;
		private static byte TYPE_GET_INTERRUPT = 8;
		private static byte TYPE_INTERRUPT = 9;

		public delegate void Interrupt(byte interruptMask, byte valueMask);

		public BrickletIO4(string uid) : base(uid) 
		{
			messageCallbacks[TYPE_INTERRUPT] = new MessageCallback(CallbackInterrupt);
		}

		public void SetValue(byte valueMask)
		{
			byte[] data = new byte[5];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_SET_VALUE, 1, data);
			LEConverter.To((ushort)5, 2, data);
			LEConverter.To(valueMask, 4, data);

			ipcon.Write(this, data, TYPE_SET_VALUE, false);
		}

		public void GetValue(out byte valueMask)
		{
			byte[] data = new byte[4];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_GET_VALUE, 1, data);
			LEConverter.To((ushort)4, 2, data);

			ipcon.Write(this, data, TYPE_GET_VALUE, true);

			byte[] answer;
			if(!answerQueue.TryDequeue(out answer, IPConnection.TIMEOUT_ANSWER))
			{
				throw new TimeoutException("Did not receive answer for GetValue in time");
			}

			valueMask = LEConverter.ByteFrom(4, answer);

			writeEvent.Set();
		}

		public void SetConfiguration(byte pinMask, char direction, bool value)
		{
			byte[] data = new byte[7];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_SET_CONFIGURATION, 1, data);
			LEConverter.To((ushort)7, 2, data);
			LEConverter.To(pinMask, 4, data);
			LEConverter.To(direction, 5, data);
			LEConverter.To(value, 6, data);

			ipcon.Write(this, data, TYPE_SET_CONFIGURATION, false);
		}

		public void GetConfiguration(out byte directionMask, out byte valueMask)
		{
			byte[] data = new byte[4];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_GET_CONFIGURATION, 1, data);
			LEConverter.To((ushort)4, 2, data);

			ipcon.Write(this, data, TYPE_GET_CONFIGURATION, true);

			byte[] answer;
			if(!answerQueue.TryDequeue(out answer, IPConnection.TIMEOUT_ANSWER))
			{
				throw new TimeoutException("Did not receive answer for GetConfiguration in time");
			}

			directionMask = LEConverter.ByteFrom(4, answer);
			valueMask = LEConverter.ByteFrom(5, answer);

			writeEvent.Set();
		}

		public void SetDebouncePeriod(uint debounce)
		{
			byte[] data = new byte[8];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_SET_DEBOUNCE_PERIOD, 1, data);
			LEConverter.To((ushort)8, 2, data);
			LEConverter.To(debounce, 4, data);

			ipcon.Write(this, data, TYPE_SET_DEBOUNCE_PERIOD, false);
		}

		public void GetDebouncePeriod(out uint debounce)
		{
			byte[] data = new byte[4];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_GET_DEBOUNCE_PERIOD, 1, data);
			LEConverter.To((ushort)4, 2, data);

			ipcon.Write(this, data, TYPE_GET_DEBOUNCE_PERIOD, true);

			byte[] answer;
			if(!answerQueue.TryDequeue(out answer, IPConnection.TIMEOUT_ANSWER))
			{
				throw new TimeoutException("Did not receive answer for GetDebouncePeriod in time");
			}

			debounce = LEConverter.UIntFrom(4, answer);

			writeEvent.Set();
		}

		public void SetInterrupt(byte interruptMask)
		{
			byte[] data = new byte[5];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_SET_INTERRUPT, 1, data);
			LEConverter.To((ushort)5, 2, data);
			LEConverter.To(interruptMask, 4, data);

			ipcon.Write(this, data, TYPE_SET_INTERRUPT, false);
		}

		public void GetInterrupt(out byte interruptMask)
		{
			byte[] data = new byte[4];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_GET_INTERRUPT, 1, data);
			LEConverter.To((ushort)4, 2, data);

			ipcon.Write(this, data, TYPE_GET_INTERRUPT, true);

			byte[] answer;
			if(!answerQueue.TryDequeue(out answer, IPConnection.TIMEOUT_ANSWER))
			{
				throw new TimeoutException("Did not receive answer for GetInterrupt in time");
			}

			interruptMask = LEConverter.ByteFrom(4, answer);

			writeEvent.Set();
		}

		public int CallbackInterrupt(byte[] data)
		{
			byte interruptMask = LEConverter.ByteFrom(4, data);
			byte valueMask = LEConverter.ByteFrom(5, data);

			((Interrupt)callbacks[TYPE_INTERRUPT])(interruptMask, valueMask);
			return 6;
		}

		public void RegisterCallback(System.Delegate d)
		{
			if(d.GetType() == typeof(Interrupt))
			{
				callbacks[TYPE_INTERRUPT] = d;
			}
		}
	}
}
