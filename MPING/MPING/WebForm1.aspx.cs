using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;
using System.Data.Common;
using System.Data.SqlClient;
using System.Data.SqlTypes;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace MPING
{
    

    public partial class WebForm1 : System.Web.UI.Page
    {


        [DllImport(@"C:\Users\g04480\Desktop\你们的小可爱\YQYQY\Debug\ContainerClass.dll")]
        extern unsafe static float* mainEntrance(float[,] inputarr, float[] fieldinfo, char[] fieldname,int itemnum);



        protected void Page_Load(object sender, EventArgs e)
        {
            //string cnnStr;
            //SqlConnection cnn;




            //cnnStr = @"Data Source =localhost;Trusted_Connection=yes";

            //cnn = new SqlConnection(cnnStr);
            //cnn.Open();

            //Response.Write("Connection Made");

            ///*test code here*/
            //String sqlSelect = "Use Qtest Select ITEM_ID,ITEM_NAME,ITEM_NOTE,ITEM_D_X,ITEM_D_Y,DES_FIELD_ID,RL_FIELD_ID from info_item";
            //String Output = "</br>";

            //SqlCommand commandSelect = new SqlCommand(sqlSelect, cnn);
            //SqlDataReader dataReader;
            //dataReader = commandSelect.ExecuteReader();
            //while (dataReader.Read())
            //{
            //    Output = Output + dataReader.GetValue(0) + "  " + dataReader.GetValue(1)
            //        + "  " + dataReader.GetValue(2) + "  " + dataReader.GetValue(3)
            //         + "  " + dataReader.GetValue(4) + "  " + dataReader.GetValue(5)
            //          + "  " + dataReader.GetValue(6) + "</br>";
            //}

            //Response.Write(Output);
            //dataReader.Close();
            //commandSelect.Dispose();
            ///*test code ends here*/

            //cnn.Close();

        }

        public string GetConnectionString()
        {
            return System.Configuration.ConfigurationManager.ConnectionStrings["MyConsString"].ConnectionString;
        }

        protected void ExecuteInsert(string id, string name, string note, int x, int y, string des)
        {

            //string cnnStr= @"Data Source =localhost;Trusted_Connection=yes";

            SqlConnection cnn = new SqlConnection(GetConnectionString());

            String sqlInsert = "Use Qtest INSERT INTO info_item (ITEM_ID,ITEM_NAME,ITEM_NOTE,ITEM_D_X,ITEM_D_Y,DES_FIELD_ID) VALUES" +
            "(@ITEM_ID,@ITEM_NAME,@ITEM_NOTE,@ITEM_D_X,@ITEM_D_Y,@DES_FIELD_ID)";
            try
            {
                
                cnn.Open();
                SqlCommand commandInsert = new SqlCommand(sqlInsert, cnn);
                SqlParameter[] param = new SqlParameter[6];

                param[0] = new SqlParameter("@ITEM_ID", SqlDbType.VarChar, 16);
                param[1] = new SqlParameter("@ITEM_NAME", SqlDbType.VarChar, 50);
                param[2] = new SqlParameter("@ITEM_NOTE", SqlDbType.VarChar, 250);
                param[3] = new SqlParameter("@ITEM_D_X", SqlDbType.Int, 100);//RANGE OF INT???
                param[4] = new SqlParameter("@ITEM_D_Y", SqlDbType.Int, 100);
                param[5] = new SqlParameter("@DES_FIELD_ID", SqlDbType.VarChar, 16);

                param[0].Value = id;
                param[1].Value = name;
                param[2].Value = note;
                param[3].Value = x;
                param[4].Value = y;
                param[5].Value = des;

                for (int i = 0; i < param.Length; i++)
                {
                    commandInsert.Parameters.Add(param[i]);
                }

                commandInsert.CommandType = CommandType.Text;
                commandInsert.ExecuteNonQuery();
                Response.Write("Insertion Succeeded");
            }
            catch (System.Data.SqlClient.SqlException ex)
            {
                string msg = "Insertion error";
                msg += ex.Message;
                //throw new Exception(msg);
                MessageBox.Show(msg,"Error");


            }
            finally
            {
                Response.Write("Insertion Secceeded");

                cnn.Close();
            }


        }

        protected void ExecuteUpdate(string id, string name, string note, int x, int y, string des)
        {

            //string cnnStr= @"Data Source =localhost;Trusted_Connection=yes";

            SqlConnection cnn = new SqlConnection(GetConnectionString());

            String sqlInsert = "Use Qtest UPDATE info_item SET ITEM_NAME=@ITEM_NAME,ITEM_NOTE=@ITEM_NOTE,ITEM_D_X=@ITEM_D_X,ITEM_D_Y=@ITEM_D_Y,DES_FIELD_ID=@DES_FIELD_ID where ITEM_ID = "+id;
            try
            {
                cnn.Open();
                //Response.Write("Connection Made");
                SqlCommand commandInsert = new SqlCommand(sqlInsert, cnn);
                SqlParameter[] param = new SqlParameter[5];

                
                param[0] = new SqlParameter("@ITEM_NAME", SqlDbType.VarChar, 50);
                param[1] = new SqlParameter("@ITEM_NOTE", SqlDbType.VarChar, 250);
                param[2] = new SqlParameter("@ITEM_D_X", SqlDbType.Int, 100);//RANGE OF INT???
                param[3] = new SqlParameter("@ITEM_D_Y", SqlDbType.Int, 100);
                param[4] = new SqlParameter("@DES_FIELD_ID", SqlDbType.VarChar, 16);

               
                param[0].Value = name;
                param[1].Value = note;
                param[2].Value = x;
                param[3].Value = y;
                param[4].Value = des;

                for (int i = 0; i < param.Length; i++)
                {
                    commandInsert.Parameters.Add(param[i]);
                }

                commandInsert.CommandType = CommandType.Text;
                commandInsert.ExecuteNonQuery();
                Response.Write(" Update Succeeded");
            }
            catch (System.Data.SqlClient.SqlException ex)
            {
                string msg = "Insertion error";
                msg += ex.Message;
                //throw new Exception(msg);
                MessageBox.Show(msg);


            }
            finally
            {
                cnn.Close();
                
            }


        }

        protected void ExecuteSearchID(String id)
        {
            //not a single verification
            SqlConnection cnn = new SqlConnection(GetConnectionString());
            try
            {
                cnn.Open();
                String sqlSelect = "Use Qtest Select PROJ_ID,WIDTH_VALUE,LENGTH_VALUE,LOC_X,LOC_Y from hull_info where ID_TEMP="+id;
               // String Output = "</br>";

                //method of binding

                SqlDataAdapter sda = new SqlDataAdapter(sqlSelect, cnn);
                DataSet ds = new DataSet();
                sda.Fill(ds);

                this.ListBox9.DataSource = ds.Tables[0].DefaultView;
                this.ListBox9.DataTextField = "PROJ_ID";
                //this.ListBox9.DataValueField = "ITEM_D_X";
                this.ListBox9.DataBind();
                this.ListBox10.DataSource = ds.Tables[0].DefaultView;
                this.ListBox10.DataTextField = "WIDTH_VALUE";
                this.ListBox10.DataBind();
                this.ListBox11.DataSource = ds.Tables[0].DefaultView;
                this.ListBox11.DataTextField = "LENGTH_VALUE";
                this.ListBox11.DataBind();
                this.ListBox12.DataSource = ds.Tables[0].DefaultView;
                this.ListBox12.DataTextField = "LOC_X";
                this.ListBox12.DataBind();
                this.ListBox13.DataSource = ds.Tables[0].DefaultView;
                this.ListBox13.DataTextField = "LOC_Y";
                this.ListBox13.DataBind();



                //SqlCommand commandSelect = new SqlCommand(sqlSelect, cnn);
                //SqlDataReader dataReader;
                //dataReader = commandSelect.ExecuteReader();
                //bool flag = false;
                //while (dataReader.Read())
                //{
                //    if(flag==false) flag=true;
                //    Output = Output + dataReader.GetValue(0) + "  " + dataReader.GetValue(1)
                //        + "  " + dataReader.GetValue(2) + "  " + dataReader.GetValue(3)
                //         + "  " + dataReader.GetValue(4) + "  " + dataReader.GetValue(5)
                //          + "  " + dataReader.GetValue(6) + "</br>";
                //    this.ListBox9.Items.Add(new ListItem(dataReader.GetValue(3).ToString()));
                //    this.ListBox10.Items.Add(dataReader.GetValue(1).ToString());
                //    this.ListBox11.Items.Add(dataReader.GetValue(4).ToString());
                //    this.ListBox12.Items.Add(dataReader.GetValue(2).ToString());
                //    this.ListBox13.Items.Add(dataReader.GetValue(6).ToString());
                //}
                //if (flag == false) Output += "No such Item";
                //Response.Write(Output);
                //dataReader.Close();
                //commandSelect.Dispose();
                /*test code ends here*/


            }
            catch (System.Data.SqlClient.SqlException ex)
            {
                string msg = "Search by ID error, please enter number, error message: ";
                msg += ex.Message;
                MessageBox.Show(msg,"Note");
                //throw new Exception(msg);
                

            }
            finally {
                cnn.Close();
            }
            
        }

        protected void ExecuteDisplayArrangement(String id)
        {
            SqlConnection cnn = new SqlConnection(GetConnectionString());
            try
            {
                cnn.Open();
                String sqlSelect = "Use Qtest Select ID_TEMP, OBJ_OUTSIDE_ID,PLAN_START,PLAN_END,WIDTH_VALUE,LENGTH_VALUE,PROJ_ID,PROJ_NAME,LOC_X,LOC_Y,ORIENTATION,ACTUAL_START,ACTUAL_END from hull_info where PROJ_ID=" + "'" + id + "'";


                SqlDataAdapter sda = new SqlDataAdapter(sqlSelect, cnn);
                DataSet ds = new DataSet();
                sda.Fill(ds,"table");
                if (ds.Tables[0].Rows.Count == 0)
                {
                    MessageBox.Show("No such project", "Error");
                    return;

                }
                GridView1.DataSource = ds.Tables["table"];
                GridView1.DataBind();
                //FOLLOWING SAVE INTO ARRAY IN1,IN2 FOR USE OF LAYOUT COMPUTATION
                
                //String sqlSelectsub = "Use Qtest Select DATEDIFF(Day,PLAN_START,PLAN_END) AS PERIOD,WIDTH_VALUE,LENGTH_VALUE from hull_info where PROJ_ID=" + "'" + id + "'";
                //SqlDataAdapter sdasub = new SqlDataAdapter(sqlSelectsub, cnn);
                //sdasub.Fill(ds, "table2");
                //GridView2.DataSource = ds.Tables["table2"];
                //GridView2.DataBind();
                //this.in1 = new float[ds.Tables["tables2"].Rows.Count, 5];
                //Response.Write(float.Parse(ds.Tables["table2"].Rows[0][1].ToString()));
/*
                for (int i = 0; i < ds.Tables["table2"].Rows.Count; i++) {
                    for (int j = 0; j < ds.Tables["tables2"].Columns.Count; j++) { 
                        if (j == 0) { 
                             this.in1[i, 0] = i;//item code
                             continue;
                        }
                        if (j == 3)
                        {
                            this.in1[i, j] = 3;//item number
                            continue;
                        }
                        this.in1[i,j] = float.Parse(ds.Tables["tables2"].Rows[i][j].ToString());
                    }
                        

                    
                }
                
   */            

                //BELOW inconvenient for adding function
                /*SqlCommand commandSelect = new SqlCommand(sqlSelect, cnn);

                this.ListBox14.Items.Clear();
                SqlDataReader dataReader;
                dataReader = commandSelect.ExecuteReader();

                bool flag = false;
                while (dataReader.Read())
                {
                    String Output = "";
                    if (flag == false) flag = true;
                    Output = Output + dataReader.GetValue(0) + "\t\t" + dataReader.GetValue(1)
                        + "\t\t" + dataReader.GetValue(2) + "\t\t" + dataReader.GetValue(3)
                         + "\t\t" + dataReader.GetValue(4) + "\t\t";
                    this.ListBox14.Items.Add(new ListItem(Output));
                    
                }
                String Outputno = "";
                if (flag == false)  Outputno = "No such Item";
                Response.Write(Outputno);
                dataReader.Close();
                commandSelect.Dispose();*/



            }
            catch (System.Data.SqlClient.SqlException ex)
            {
                string msg = "Search by Field ID error, please enter number, error message: ";
                msg += ex.Message;
                MessageBox.Show(msg, "Note");
                //throw new Exception(msg);


            }
            finally
            {
                cnn.Close();
            }
 
        }

        protected void ExecuteInsertLayout(float[] in1, int numselected, String id, SqlConnection cnn)//used in ExecuteCompute()
        { //fcn in excuteCompute
            String sqlupdate = "Use Qtest UPDATE hull_info SET LOC_X= @LOC_X,LOC_Y=@LOC_Y,ORIENTATION=@ORIENTATION,OFFSET=@OFFSET WHERE ID_TEMP = ";
            
            SqlParameter[] param = new SqlParameter[4];


            param[0] = new SqlParameter("@LOC_X", SqlDbType.Float,50);
            param[1] = new SqlParameter("@LOC_Y", SqlDbType.Float, 50);
            param[2] = new SqlParameter("@ORIENTATION", SqlDbType.VarChar, 50);
            param[3] = new SqlParameter("@OFFSET", SqlDbType.Float, 100);
            //param[3] = new SqlParameter("@ACTUAL_START", SqlDbType.DateTime, 100);//RANGE OF INT???
            //param[3] = new SqlParameter("@ACTUAL_END", SqlDbType.DateTime, 100);//RANGE OF INT???
            //int qwee = 0;//lines influenced
            for (int i = 0; i < numselected; i++) {
                
                

                param[0].Value = in1[i * 8 + 5];
                param[1].Value = in1[i * 8 + 6];
                param[2].Value = in1[i * 8 + 4];
                param[3].Value = in1[i * 8 + 7];

                float id2id = in1[i * 8 + 0];
                SqlCommand commandInsert = new SqlCommand(sqlupdate + id2id.ToString(), cnn);
                
                for (int k = 0; k < param.Length; k++)
                {
                    commandInsert.Parameters.Add(param[k]);
                }

                commandInsert.CommandType = CommandType.Text;
                //qwee=
                commandInsert.ExecuteNonQuery();
                //Response.Write(qwee);
                commandInsert.Parameters.Clear();

            }
               
            Response.Write("Update Succeeded");
        }

        protected void ExecuteCompute(String id) { 

            SqlConnection cnn = new SqlConnection(GetConnectionString());
            try
            {
                cnn.Open();



                //FOLLOWING SAVE INTO ARRAY IN1,IN2 FOR USE OF LAYOUT COMPUTATION
                //!!!!!!!!!!!!!ONLY AREA !=0 SELECTED

                /*Read field info*/

                String sqlSelect = "Use Qtest Select FLD_X,FLD_Y from field_info where FIELD_ID=" + this.TextBoxFieldId.Text;
                SqlCommand commandSelect = new SqlCommand(sqlSelect, cnn);
                SqlDataReader dataReader = commandSelect.ExecuteReader();
                String Output;
                float a, b;
                if (dataReader.Read() && dataReader.GetValue(0) != null && dataReader.GetValue(1) != null)
                {

                    Output = "Width: " + dataReader.GetValue(0).ToString() + "Length: " + dataReader.GetValue(1).ToString();
              
                    this.ListBoxField.Items.Add(Output);
                    a = float.Parse(dataReader.GetValue(0).ToString());
                    b = float.Parse(dataReader.GetValue(0).ToString());
                    dataReader.Close();
                }
                else
                {
                    MessageBox.Show("Please enter field to be put", "Error");
                    return;

                }

                /*end read field info*/
                DataSet ds = new DataSet();
                String sqlSelectsub = "Use Qtest Select ID_TEMP,WIDTH_VALUE,LENGTH_VALUE,DATEDIFF(Day,PLAN_START,PLAN_END) AS PERIOD from hull_info where PROJ_ID=" + "'" + id + "' and WIDTH_VALUE!=0 and LENGTH_VALUE!=0";
                SqlDataAdapter sdasub = new SqlDataAdapter(sqlSelectsub, cnn);
                sdasub.Fill(ds);
                //GridView2.DataSource = ds.Tables[0];
                //GridView2.DataBind();
                //Response.Write(ds.Tables[0].Columns.Count);

               

                if (ds.Tables[0].Rows.Count == 0) {
                    MessageBox.Show("No such project","Error");
                    return;
                
                }
                float[,] in1 = new float[ds.Tables[0].Rows.Count, 5];
                float[] in2 = new float[] {a,b };

                //float[,] in1 = { { 1, 3, 6, 3, 1 }, { 2, 1, 4, 2, 1 }, { 3, 1, 2, 1, 1 }, { 4, 2, 2, 2, 1 }, { 5, 2, 2, 1, 1 } };

                //float[] in2 = new float[] { 5, 4 };

                for (int i = 0; i < ds.Tables[0].Rows.Count; i++)
                {
                    for (int j = 0; j < 5; j++)
                    {
                        //if (float.Parse(ds.Tables[0].Rows[i][0].ToString()) == 0 || float.Parse(ds.Tables[0].Rows[i][1].ToString()) == 0)
                        //{
                        //   Response.Write("WIDTH OR LENGTH==ZERO: # " + i);
                        //    continue;
                        //}
                        if (j == 0)
                        {
                            in1[i, 0] = float.Parse(ds.Tables[0].Rows[i][0].ToString());//item code
                            continue;
                        }
                        if (j == 4)
                        {
                            in1[i, j] = 1;//item quantity
                            continue;
                        }

                        in1[i, j] = float.Parse(ds.Tables[0].Rows[i][j].ToString());
                        //DIVIDE BY ZERO IF BOTTON AREA =0
                        if (in1[i, 1] == 0) in1[i, 1] = 0.1F;
                        if (in1[i, 2] == 0) in1[i, 2] = 0.1F;
                    }



                }
                /*
                //test input correctness
                for (int i = 0; i < ds.Tables[0].Rows.Count; i++)
                {
                    Response.Write("{");
                    for (int j = 0; j < ds.Tables[0].Columns.Count + 2; j++)
                    {
                        Response.Write(in1[i, j] + ",");
                    }
                    Response.Write("}<br/>");
                }
                */
                //start compute using extern fcn in dll

                unsafe
                {
                    float* ret = mainEntrance(in1, in2, "qwerty".ToCharArray(), in1.GetLength(0));//return value not drawn,in1.getlength(0)item number selected
                    //PRINT BUT NOT UPDATE IN DB
                      //Response.Write("In c#:<br/>");
                    DataTable dtprint = new DataTable();
                    for (int j = 0; j < 8; j++)
                    {
                        DataColumn newcol = new DataColumn(j.ToString(), ret[0].GetType());
                        dtprint.Columns.Add(newcol);
                    }

                      for (int i = 0; i < in1.GetLength(0); i++)
                      {
                          DataRow newrow = dtprint.NewRow();
                          for (int j = 0; j < 8; j++) {
                              newrow[j.ToString()] = ret[i * 8 + j];
                          }
                          dtprint.Rows.Add(newrow);
                      }

                      GridView2.DataSource=dtprint;
                      GridView2.DataBind();
                    //ans array for fcn executeinsertlayout
                    float[] ans = new float[in1.GetLength(0) * 8];
                    for (int i = 0; i < in1.GetLength(0); i++)
                    {
                        for (int j = 0; j < 8; j++)
                        {
                            ans[i * 8 + j] = ret[i * 8 + j];
                        }

                    }

                    if (CheckBoxUpdate.Checked)
                        ExecuteInsertLayout(ans, in1.GetLength(0), id, cnn);
                }

                //insert into db



            }
            catch (System.Data.SqlClient.SqlException ex)
            {
                string msg = "Search by PROJ_ID OR FIELD_IDerror, please enter number, error message: ";
                msg += ex.Message;
                MessageBox.Show(msg, "Note");
            }
            catch (Exception e) {
                MessageBox.Show(e.Message, "Error");
            }
            finally
            {
                cnn.Close();
            }
 
        }
    

        protected void ButtonSearch_click(object sender, EventArgs e)
        {
            ExecuteSearchID(TextBoxID0.Text);

        }

        protected void ButtonAdd_click(object sender, EventArgs e)
        {
            //for test
            //ExecuteInsert("134", "lalal", "what you want me to say", 12, 32, "002");
            try {
                ExecuteInsert(TextBoxID.Text, TextBoxNAME.Text, TextBoxNOTE.Text, int.Parse(TextBoxWIDTH.Text), int.Parse(TextBoxLENGTH.Text), TextBoxDESDES.Text);
            }
            catch(FormatException ex){
                string msg = "Insertion error: Please fill all info! :";
                msg += ex.Message;
                //throw new Exception(msg);
                MessageBox.Show(msg,"Error");
            
            }
            finally{

            }
            

        }


        protected void ButtonDisplay_click(object sender, EventArgs e)
        {
            ExecuteDisplayArrangement(TextBoxProjId.Text);

            

            
        }



        protected void ButtonCalculate_Click(object sender, EventArgs e)
        {
            //float[,] in1 = { { 1, 3, 6, 3, 1 }, { 2, 1, 4, 2, 1 }, { 3, 1, 2, 1, 1 }, { 4, 2, 2, 2, 1 }, { 5, 2, 2, 1, 1 } };

            //float[] in2 = new float[] { 5, 4 };
            try
            {
                ExecuteCompute(TextBoxProjId.Text);
            }
            catch (Exception ex)
            {
                string msg = "Insertion error: Please fill in correct object number! :";
                msg += ex.Message;
                //throw new Exception(msg);
                MessageBox.Show(msg, "Error");

            }
            finally
            {
            }

        }

        protected void ButtonAdd1_click(object sender, EventArgs e)
        {
            try {
            ExecuteUpdate(TextBoxID.Text, TextBoxNAME.Text, TextBoxNOTE.Text, int.Parse(TextBoxWIDTH.Text), int.Parse(TextBoxLENGTH.Text), TextBoxDESDES.Text);
            }
            catch (FormatException ex)
            {
                string msg = "Insertion error: Please fill in all info! :";
                msg += ex.Message;
                //throw new Exception(msg);
                MessageBox.Show(msg, "Error");

            }
            finally
            {

            }
        }

       


    }
}