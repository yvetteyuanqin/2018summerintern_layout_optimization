<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="WebForm1.aspx.cs" Inherits="MPING.WebForm1" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>Item Info Management</title>
    <style type="text/css">
        .style1
        {
            height: 36px;
            width: 281px;
        }
        .style2
        {
            width: 51px;
            height: 44px;
        }
        .style3
        {
            height: 36px;
            width: 51px;
        }
        .style4
        {
            width: 43px;
            height: 44px;
        }
        .style5
        {
            height: 36px;
            width: 43px;
        }
        .style6
        {
            width: 281px;
            height: 44px;
        }
        #Text1
        {
            height: 21px;
            width: 295px;
        }
        .style7
        {
            width: 51px;
            height: 37px;
        }
        .style8
        {
            width: 281px;
            height: 37px;
        }
        .style9
        {
            width: 43px;
            height: 37px;
        }
        .style10
        {
            height: 37px;
        }
        .style11
        {
            height: 44px;
        }
        </style>
    <script language="javascript" type="text/javascript">
// <![CDATA[

        function Text1_onclick() {

        }

// ]]>
    </script>
</head>
<body>
    <form id="form1" runat="server">
     <div  style="border: thin none #0000FF; background-color: #38a; height: 44px; padding-top:5px; width: 786px;"
         style="height: 24px; width: 770px">
        <asp:Label ID="Label14" runat="server" style="padding-left:300px; font-family: 宋体; font-size: x-large; font-weight: 600; font-style: normal; font-variant: normal; text-transform: none;" Text="ITEM INFO"></asp:Label>
    </div>
    <div>
        <table style="width: 55%; height: 157px;">
            <tr>
                <td class="style2">
                    <asp:Label ID="Label8" runat="server" Text="ID"></asp:Label>
                </td>
                <td class="style6">
                    <asp:TextBox ID="TextBoxID0" runat="server" Width="294px" 
                       ></asp:TextBox>
                </td>
                <td class="style4">
                    <asp:Label ID="Label9" runat="server" Text="PROJ_ID"></asp:Label>
                </td>
                <td class="style11">
                    <asp:ListBox ID="ListBox9" runat="server" Height="20px" Width="299px" 
                       >
                    </asp:ListBox>
                </td>
            </tr>
            <tr>
                <td class="style3">
                    <asp:Label ID="Label10" runat="server" Text="WIDTH"></asp:Label>
                </td>
                <td class="style1">
                    <asp:ListBox ID="ListBox10" runat="server" Height="20px" Width="307px">
                    </asp:ListBox>
                </td>
                <td class="style5">
                    <asp:Label ID="Label11" runat="server" Text="LENGTH"></asp:Label>
                </td>
                <td>
                    <asp:ListBox ID="ListBox11" runat="server" Height="20px" Width="296px">
                    </asp:ListBox>
                </td>
            </tr>
            <tr>
                <td class="style7">
                    <asp:Label ID="Label12" runat="server" Text="LOC_X"></asp:Label>
                </td>
                <td class="style8">
                    <asp:ListBox ID="ListBox12" runat="server" Height="20px" Width="307px" >
                    </asp:ListBox>
                </td>
                <td class="style9">
                    <asp:Label ID="Label13" runat="server" Text="LOC_Y
                    "></asp:Label>
                </td>
                <td class="style10">
                    <asp:ListBox ID="ListBox13" runat="server" Height="20px" Width="307px">
                    </asp:ListBox>
                </td>
            </tr>
        </table>
    </div>
    <div  style="border: thin none #0000FF; background-color: #333; height: 25px; padding-top:5px"style="height: 24px; width: 770px">
        <asp:Button BackColor=AliceBlue Font-Bold=true ID="ButtonSearch" runat="server" onclick="ButtonSearch_click" 
            Text="SEARCH BY ID"  />
        <br />
    <div style="border: thin none #0000FF; background-color: #38a; height: 35px; padding-top:5px" style="height: 41px; width: 772px;">
    
        <asp:Label ID="Label7" runat="server" style="padding-left:300px; font-family: 宋体; font-size: x-large; font-weight: 800; font-style: normal; font-variant: normal; text-transform: none;" Text="UPDATE ITEM"></asp:Label>
    
    </div>
    <div style="height: 160px; width: 772px">
        <table style="width: 100%; height: 157px;">
            <tr>
                <td class="style2">
                    <asp:Label ID="Label1" runat="server" Text="ID"></asp:Label>
                </td>
                <td class="style6">
                    <asp:TextBox ID="TextBoxID" runat="server" Width="294px"></asp:TextBox>
                </td>
                <td class="style4">
                    <asp:Label ID="Label4" runat="server" Text="WIDTH"></asp:Label>
                </td>
                <td class="style11">
                    <asp:TextBox ID="TextBoxWIDTH" runat="server" Width="294px"></asp:TextBox>
                </td>
            </tr>
            <tr>
                <td class="style3">
                    <asp:Label ID="Label2" runat="server" Text="NAME"></asp:Label>
                </td>
                <td class="style1">
                    <asp:TextBox ID="TextBoxNAME" runat="server" Width="294px"></asp:TextBox>
                </td>
                <td class="style5">
                    <asp:Label ID="Label5" runat="server" Text="LENGTH"></asp:Label>
                </td>
                <td>
                    <asp:TextBox ID="TextBoxLENGTH" runat="server" Width="294px"></asp:TextBox>
                </td>
            </tr>
            <tr>
                <td class="style7">
                    <asp:Label ID="Label3" runat="server" Text="NOTE"></asp:Label>
                </td>
                <td class="style8">
                    <asp:TextBox ID="TextBoxNOTE" runat="server" Width="294px"></asp:TextBox>
                </td>
                <td class="style9">
                    <asp:Label ID="Label6" runat="server" Text="DESIRED DESTINATION
                    "></asp:Label>
                </td>
                <td class="style10">
                    <asp:TextBox ID="TextBoxDESDES" runat="server" Width="294px"></asp:TextBox>
                </td>
            </tr>
        </table>
    </div>
    <div  style="border: thin none #0000FF; background-color: #333; height: 25px; padding-top:5px"style="height: 24px; width: 770px">
        <asp:Button BackColor=AliceBlue Font-Bold=true ID="ButtonAdd" runat="server" onclick="ButtonAdd_click" Text="INSERT NEW" />
    &nbsp;
        <asp:Button BackColor=AliceBlue Font-Bold=true ID="ButtonAdd1" runat="server" 
            onclick="ButtonAdd1_click" Text="UPDATE" />
    </div>
     <div  style="border: thin none #0000FF; background-color: #38a; height: 35px; padding-top:5px; margin-top: 0px;"
            style="height: 24px; width: 770px">
        <asp:Label ID="Label15" runat="server" 
             style="padding-left:300px; font-family: 宋体; font-size: x-large; font-weight: 600; font-style: normal; font-variant: normal; text-transform: none;" 
             Text="LAYOUT MANAGEMENT"></asp:Label>
    </div>
        <br />
        <div>
                    <asp:Label ID="Label16" runat="server" Text="Project id NO.: "></asp:Label>
                    <asp:TextBox ID="TextBoxProjId" runat="server" Width="149px" 
                        Text="Pls Enter Project ID" Height="18px" 
                       ></asp:TextBox>
                    <asp:Label ID="Label17" runat="server" Text="Field to put:: "></asp:Label>
                    <asp:TextBox ID="TextBoxFieldId" runat="server" Width="82px"></asp:TextBox>
                    <asp:Label ID="Label18" runat="server" Text="Field Info "></asp:Label>
                    <asp:ListBox ID="ListBoxField" BackColor=HotTrack runat="server" Height="22px" Width="149px">
                    </asp:ListBox>
                </div>
       
        
        <br />
    <div  style="border: thin none #0000FF; background-color: #333; height: 25px; padding-top:5px"style="height: 24px; width: 770px">
        <asp:Button BackColor=AliceBlue Font-Bold=true ID="ButtonDisplay" 
            runat="server" onclick="ButtonDisplay_click"            
            Text="Display Items in this field" 
            Width="228px" />
        &nbsp;&nbsp;<asp:Button BackColor=AliceBlue Font-Bold=true 
            ID="ButtonCalculate" runat="server" Text="Compute Layout or Update" 
            onclick="ButtonCalculate_Click" Width="288px" />
        &nbsp;<asp:CheckBox ID="CheckBoxUpdate" runat="server" Text="UPDATE location into DB" BackColor=Info />
        <br />
        <div>
            <asp:GridView ID="GridView2" runat="server" Height="67px" Width="765px">
            </asp:GridView>
            <asp:GridView ID="GridView1" runat="server" Width="769px" BackColor=Beige 
                BorderColor=Brown >
            </asp:GridView>
            <br />
        </div>
    </div>
    </div>
    </form>
    
    </body>
</html>
