using System;
using System.Data;
using System.Linq;
using System.Windows.Forms;
using System.IO.Ports;
using System.Drawing;
using System.Threading;
using System.Text.RegularExpressions;
using System.Collections.Generic;
using System.Text;

namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        const byte SLAVE1_ADDRESS = 0x0B;
        const byte SLAVE2_ADDRESS = 0xEA;

        public Form1()
        {
            InitializeComponent();
        }

        private void comboBox1_Click(object sender, EventArgs e)
        {
            int num;
            comboBox1.Items.Clear();
            string[] ports = SerialPort.GetPortNames().OrderBy(a => a.Length > 3 && int.TryParse(a.Substring(3), out num) ? num : 0).ToArray();
            comboBox1.Items.AddRange(ports);
        }

        private void buttonOpenPort_Click(object sender, EventArgs e)
        {
            if (!serialPort1.IsOpen)
                try
                {
                    serialPort1.PortName = comboBox1.Text;
                    serialPort1.Open();
                    buttonOpenPort.Text = "Close";
                    comboBox1.Enabled = false;
                    button1.Visible = true;
                    textBox3.Visible = true;
                    button2.Visible = true;
                    textBox1.Visible = true;
                }
                catch
                {
                    MessageBox.Show("Port " + comboBox1.Text + " is invalid!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            else
            {
                serialPort1.Close();
                buttonOpenPort.Text = "Open";
                comboBox1.Enabled = true;
                button1.Visible = false;
                textBox3.Visible = false;
                button2.Visible = false;
                textBox1.Visible = false;
            }
        }

        public static ushort Compute_CRC16(byte[] bytes)
        {
            const ushort generator = 0x1021;
            ushort crc = 0xC6C6;

            foreach (byte b in bytes)
            {
                crc ^= (ushort)(b << 8);

                for (int i = 0; i < 8; i++)
                {
                    if ((crc & 0x8000) != 0)
                    {
                        crc = (ushort)((crc << 1) ^ generator);
                    }
                    else
                    {
                        crc <<= 1;
                    }
                }
            }
            ushort myNewResult = Reflect16(crc);
            return myNewResult;
        }

        public static ushort Reflect16(ushort val)
        {
            ushort resVal = 0;

            for (int i = 0; i < 16; i++)
            {
                if ((val & (1 << i)) != 0)
                {
                    resVal |= (ushort)(1 << (15 - i));
                }
            }

            return resVal;
        }

        public static byte ReverseByte(byte b)
        {
            int a = 0;
            for (int i = 0; i < 8; i++)
                if ((b & (1 << i)) != 0)
                    a |= 1 << (7 - i);
            return (byte)a;
        }

        public int CombineBytes(byte b1, byte b2)
        {
            int combined = b1 << 8 | b2;
            return combined;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            byte[] b1 = new byte[3];
            b1[0] = SLAVE1_ADDRESS;
            b1[1] = 0xB1;
            serialPort1.Write(b1, 0, 2);

            List<byte> byteListHum = new List<byte>();
            List<byte> byteListTemp = new List<byte>();

            for (int i = 0; i < 8; i++)
            {
                if (i < 4)
                {
                    byte info_hum = (byte)serialPort1.ReadByte();
                    byteListHum.Add(info_hum);
                } else
                {
                    byte info_temp = (byte)serialPort1.ReadByte();
                    byteListTemp.Add(info_temp);
                }
                
            }
            float[] myFloatArrayHum = ConvertByteToFloat(byteListHum.ToArray());
            float[] myFloatArrayTemp = ConvertByteToFloat(byteListTemp.ToArray());
            textBox3.Text = "Humidity: " + myFloatArrayHum[0].ToString() + " %" + "   " + "Temperature: " +  myFloatArrayTemp[0].ToString() + " C";
        }

        public static float[] ConvertByteToFloat(byte[] array)
        {
            float[] floatArr = new float[array.Length / 4];
            for (int i = 0; i < floatArr.Length; i++)
            {
                if (BitConverter.IsLittleEndian)
                {
                    Array.Reverse(array, i * 4, 4);
                }
                floatArr[i] = BitConverter.ToSingle(array, i * 4);
            }
            return floatArr;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            byte[] b1 = new byte[3];
            b1[0] = SLAVE2_ADDRESS;
            b1[1] = 0xB1;
            serialPort1.Write(b1, 0, 2);

            List<byte> byteListHum = new List<byte>();
            List<byte> byteListTemp = new List<byte>();

            for (int i = 0; i < 8; i++)
            {
                if (i < 4)
                {
                    byte info_hum = (byte)serialPort1.ReadByte();
                    byteListHum.Add(info_hum);
                }
                else
                {
                    byte info_temp = (byte)serialPort1.ReadByte();
                    byteListTemp.Add(info_temp);
                }

            }
            float[] myFloatArrayHum = ConvertByteToFloat(byteListHum.ToArray());
            float[] myFloatArrayTemp = ConvertByteToFloat(byteListTemp.ToArray());
            textBox1.Text = "Humidity: " + myFloatArrayHum[0].ToString() + " %" + "   " + "Temperature: " + myFloatArrayTemp[0].ToString() + " C";
        }
    }
}
