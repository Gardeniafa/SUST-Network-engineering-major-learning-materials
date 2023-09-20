import javax.swing.*;
import javax.swing.table.*;
import java.awt.*;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.io.Serial;
import java.util.ArrayList;

public class sysManager {
    private final LoginUser user;
    private JFrame sysManagerFrame;
    private final dataOperate dataOperator;
    // define table area work mode
    // 0 -> search, 1 -> add, 2 -> update, 3 -> deletion,
    private int tableAreaWorkMode;
    // table data cache
    private String[][] tableData;
    private int tablePageCounter;
    private int tableColumnNum;
    private int totalPageNum;
    // table area control
    private final int tablePageRowNum = 16;
    private final String[] schoolsTableHead = new String[]{"ID", "名称", "地址", "幼儿人数", "教工人数", "园长", "联系电话"};
//    private final String[] usersTableHead = new String[]{"ID", "名称", "权限", "密码"};
    private String[] tableHead;
    private boolean tableShowOperateStatus = false;
    private int[] tableOperateStatus;
    // page element
    private JButton previousPage;
    private JButton nextPage;
    private JLabel pageCounterLabel;
    private JPanel tableBar;
    private JTextField searchInfBox;
    private JButton inquireById;
    private JLabel tableAreaTopBarStatus;
    private JLabel tableAreaForegroundReminder;
    private JButton inquireByName;
    private JButton inquireByAddress;
    private JButton inquireByDean;
    private JTextField rangeMinValue;
    private JTextField rangeMaxValue;
    private JButton inquireByChildrenNumRange;
    private JButton inquireByEmployeeNumRange;
    private JButton addRecord;
    private JButton reviseRecord;
    private JButton deleteRecord;
    private JLabel errorReport;
    private JPanel tableAreaForeground;
    private ArrayList<String> deletedRow;
    private int lastChooseRowIndex;
    private String[] lastChooseRowData;
    public sysManager(LoginUser loginUser) throws sysManagerException{
        user = loginUser;
        try{
            this.dataOperator = new dataOperate();
        }catch (dataOperateException e){
            throw new sysManagerException("sysManager error: failed to create data operator: "+e);
        }
        this.createWindow();
    }
    private void createWindow(){
        this.sysManagerFrame = new JFrame();
        sysManagerFrame.setLayout(null);
        sysManagerFrame.setSize(790, 500);
        sysManagerFrame.setResizable(false);
        sysManagerFrame.setBackground(new Color(240,248,255));
        this.createTopBar();
        this.createLeftBar();
        this.createTableArea();
        this.createListener();
        this.sysManagerFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.sysManagerFrame.setLocationRelativeTo(null);
        this.sysManagerFrame.setVisible(true);
    }
    private void createTopBar(){
        JPanel topBar = new JPanel();
        topBar.setLayout(null);
        topBar.setBounds(0, 0, 790, 45);
        topBar.setBackground(new Color(199,217,235));
        JLabel title_zh = new JLabel("幼儿园管理系统");
        title_zh.setFont(new Font("楷体", Font.PLAIN, 24));
        title_zh.setBounds(14, 0, 168, 35);
        JLabel title_en = new JLabel("Kindergarten manage system");
        title_en.setBounds(14, 28, 150, 15);
        title_en.setFont(new Font("TimesNewRoman", Font.PLAIN, 10));
        topBar.add(title_zh);
        topBar.add(title_en);
        this.sysManagerFrame.add(topBar);
    }
    private void createLeftBar(){
        JPanel leftBar = new JPanel();
        leftBar.setLayout(null);
        leftBar.setBounds(0, 53, 150, 413);
        leftBar.setBackground(new Color(235,242,249));
        JPanel userInfBar = new JPanel();
        userInfBar.setLayout(null);
        userInfBar.setBounds(5, 9, 140, 99);
        userInfBar.setBackground(new Color(234,215,223));
        JLabel userNameFinal = new JLabel("当前用户");
        userNameFinal.setFont(new Font("", Font.PLAIN, 11));
        userNameFinal.setBounds(13, 12, 45, 16);
        userInfBar.add(userNameFinal);
        JLabel userName = new JLabel(user.name());
        userName.setFont(new Font("", Font.BOLD, 13));
        userName.setForeground(Color.red);
        userName.setBounds(25, 30, 100, 23);
        userInfBar.add(userName);
        JLabel userPermissionFinal = new JLabel("权限");
        userPermissionFinal.setFont(new Font("", Font.PLAIN, 11));
        userPermissionFinal.setBounds(13, 58, 25, 19);
        userInfBar.add(userPermissionFinal);
        JLabel userPermission = new JLabel(user.permission());
        userPermission.setFont(new Font("", Font.BOLD, 13));
        userPermission.setForeground(Color.red);
        userPermission.setBounds(25, 73, 120, 20);
        userInfBar.add(userPermission);
        leftBar.add(userInfBar);
        // create function bar
        JPanel functionBar = new JPanel();
        functionBar.setLayout(null);
        functionBar.setBounds(5, 120, 140, 289);
        functionBar.setBackground(new Color(234,215,223));
        // crate search bar
        Font fontSize10 = new Font("", Font.PLAIN, 10);
        Font fontSize11 = new Font("", Font.PLAIN, 11);
        JPanel searchBar = new JPanel();
        searchBar.setLayout(null);
        searchBar.setBackground(new Color(217,234,241));
        searchBar.setBounds(4, 4, 132,162);
        JLabel searchTitle = new JLabel("查询信息");
        searchTitle.setFont(new Font("", Font.PLAIN, 13));
        searchTitle.setBounds(9, 5, 60, 20);
        searchBar.add(searchTitle);
        JLabel searchByInfTitle = new JLabel("按照给定信息查询");
        searchByInfTitle.setFont(fontSize11);
        searchByInfTitle.setBounds(9, 27, 97, 16);
        searchBar.add(searchByInfTitle);
        JLabel searchByInfHead = new JLabel("信息：");
        searchByInfHead.setFont(fontSize10);
        searchByInfHead.setBounds(9, 45, 30, 15);
        searchBar.add(searchByInfHead);
        this.searchInfBox = new JTextField();
        searchInfBox.setBounds(35, 45, 90, 18);
        searchBar.add(searchInfBox);
        this.inquireById = new JButton("查找ID");
        inquireById.setFont(fontSize10);
        inquireById.setBounds(10, 66, 55, 15);
        searchBar.add(inquireById);
        this.inquireByName = new JButton("查找校名");
        inquireByName.setFont(fontSize10);
        inquireByName.setBounds(70, 66, 55, 15);
        searchBar.add(inquireByName);
        this.inquireByAddress = new JButton("查找地址");
        inquireByAddress.setFont(fontSize10);
        inquireByAddress.setBounds(10, 83, 55, 15);
        searchBar.add(inquireByAddress);
        this.inquireByDean = new JButton("查找园长");
        inquireByDean.setFont(fontSize10);
        inquireByDean.setBounds(70, 83, 55, 15);
        searchBar.add(inquireByDean);
        JLabel searchByRangeTitle = new JLabel("按给定范围查询：");
        searchByRangeTitle.setFont(fontSize11);
        searchByRangeTitle.setBounds(9, 101, 88, 16);
        searchBar.add(searchByRangeTitle);
        JLabel searchByRangeHead = new JLabel("范围：");
        searchByRangeHead.setFont(fontSize10);
        searchByRangeHead.setBounds(9, 118, 30, 18);
        searchBar.add(searchByRangeHead);
        this.rangeMinValue = new JTextField();
        rangeMinValue.setBounds(36, 119, 42, 16);
        rangeMinValue.setFont(fontSize10);
        searchBar.add(rangeMinValue);
        JLabel searchByRangePreposition = new JLabel("至");
        searchByRangePreposition.setFont(fontSize10);
        searchByRangePreposition.setBounds(78, 119, 10, 15);
        searchBar.add(searchByRangePreposition);
        this.rangeMaxValue = new JTextField();
        rangeMaxValue.setBounds(87, 119, 42, 16);
        rangeMaxValue.setFont(fontSize10);
        searchBar.add(rangeMaxValue);
        this.inquireByChildrenNumRange = new JButton("幼儿人数");
        inquireByChildrenNumRange.setFont(fontSize10);
        inquireByChildrenNumRange.setBounds(8, 136, 56, 16);
        searchBar.add(inquireByChildrenNumRange);
        this.inquireByEmployeeNumRange = new JButton("教工人数");
        inquireByEmployeeNumRange.setFont(fontSize10);
        inquireByEmployeeNumRange.setBounds(70, 136, 56, 16);
        searchBar.add(inquireByEmployeeNumRange);
        functionBar.add(searchBar);
        // create other bar
        JPanel addRecordBar = new JPanel();
        addRecordBar.setLayout(null);
        addRecordBar.setBounds(4, 170, 132, 25);
        addRecordBar.setBackground(new Color(217,234,241));
        this.addRecord = new JButton("增加记录");
        addRecord.setFont(new Font("", Font.PLAIN, 13));
        addRecord.setBounds(0, 0, 132, 25);
        addRecord.setContentAreaFilled(false);
        addRecord.setBorderPainted(false);
        addRecordBar.add(addRecord);
        functionBar.add(addRecordBar);
        JPanel reviseRecordBar = new JPanel();
        reviseRecordBar.setLayout(null);
        reviseRecordBar.setBounds(4, 200, 132, 25);
        reviseRecordBar.setBackground(new Color(217,234,241));
        this.reviseRecord = new JButton("修改记录");
        reviseRecordBar.setFont(new Font("", Font.PLAIN, 13));
        reviseRecord.setBounds(0, 0, 132, 26-1);
        reviseRecord.setBorderPainted(false);
        reviseRecord.setContentAreaFilled(false);
        reviseRecordBar.add(reviseRecord);
        functionBar.add(reviseRecordBar);
        JPanel deleteRecordBar = new JPanel();
        deleteRecordBar.setLayout(null);
        deleteRecordBar.setBounds(4, 230, 132, 25);
        deleteRecordBar.setBackground(new Color(217,234,241));
        this.deleteRecord = new JButton("删除记录");
        deleteRecordBar.setFont(new Font("", Font.PLAIN, 13));
        deleteRecord.setBounds(0, 0, 132, 27-2);
        deleteRecord.setContentAreaFilled(false);
        deleteRecord.setBorderPainted(false);
        deleteRecordBar.add(deleteRecord);
        functionBar.add(deleteRecordBar);
        // too difficult to develop this function, fuck
        JPanel userManagerBar = new JPanel();
        userManagerBar.setLayout(null);
        userManagerBar.setBounds(4, 260, 132, 25);
        userManagerBar.setBackground(new Color(217,234,241));
        JButton userManager = new JButton("用户管理");
        userManagerBar.setFont(new Font("", Font.PLAIN, 13));
        userManager.setBounds(0, 0, 132, 25);
        userManager.setBorderPainted(false);
        userManager.setContentAreaFilled(false);
//.        userManagerBar.add(userManager);
//.        functionBar.add(userManagerBar);

        if(!this.user.permission().equals("admin")){
            addRecord.setEnabled(false);
            reviseRecord.setEnabled(false);
            deleteRecord.setEnabled(false);
            userManager.setEnabled(false);
        }
        leftBar.add(functionBar);
        this.sysManagerFrame.add(leftBar);
    }
    private void createTableArea(){
        JPanel tableAreaBackground = new JPanel();
        tableAreaBackground.setBounds(160, 53, 621, 409);
        tableAreaBackground.setBackground(new Color(234,215,223));
        JPanel tableAreaTopBar = new JPanel();
        tableAreaTopBar.setLayout(null);
        tableAreaTopBar.setBounds(166, 58, 616, 54);
        tableAreaTopBar.setBackground(new Color(235,242,249));
        this.tableAreaForeground = new JPanel();
        tableAreaForeground.setLayout(null);
        tableAreaForeground.setBounds(166, 115, 616, 348);
        tableAreaForeground.setBackground(new Color(235,242,249));
        this.tableAreaTopBarStatus = new JLabel("全部信息");
        tableAreaTopBarStatus.setFont(new Font("", Font.PLAIN, 24));
        tableAreaTopBarStatus.setBounds(24, 8, 460, 36);
        tableAreaTopBar.add(tableAreaTopBarStatus);
        this.tableAreaForegroundReminder = new JLabel("以下为数据库中所包含的所有的幼儿园信息");
        tableAreaForegroundReminder.setFont(new Font("", Font.PLAIN, 11));
        tableAreaForegroundReminder.setBounds(26, 14, 499, 18);
        tableAreaForeground.add(tableAreaForegroundReminder);
        this.tableBar = new JPanel();
        tableBar.setBounds(24, 35, 570, 270);
        tableBar.setLayout(null);
        tableAreaForeground.add(tableBar);
        this.tableAreaWorkMode = 0;
        this.pageCounterLabel = new JLabel("第1/1页");
        pageCounterLabel.setFont(new Font("", Font.PLAIN, 11));
        pageCounterLabel.setBounds(402, 323, 48, 16);
        tableAreaForeground.add(pageCounterLabel);
        this.previousPage = new JButton("上一页");
        previousPage.setFont(new Font("", Font.PLAIN, 11));
        previousPage.setBounds(453, 323, 48, 16);
        tableAreaForeground.add(previousPage);
        this.nextPage = new JButton("下一页");
        nextPage.setFont(new Font("", Font.PLAIN, 11));
        nextPage.setBounds(516, 323, 48, 16);
        tableAreaForeground.add(nextPage);
        String[][] allInf = this.getAllRowOfSchoolsInf();
        this.createTable(allInf, this.schoolsTableHead);
        this.sysManagerFrame.add(tableAreaTopBar);
        this.sysManagerFrame.add(tableAreaForeground);
        this.sysManagerFrame.add(tableAreaBackground);
    }

    private void updateMainTable(String[][] data, String[] columns){
        this.tableBar.removeAll();
        if(this.tableShowOperateStatus){
            String[] columnsTemp = new String[this.tableColumnNum+1];
            System.arraycopy(columns, 0, columnsTemp, 0, this.tableColumnNum);
            columnsTemp[this.tableColumnNum] = "状态";
            columns = columnsTemp;
        }
        JTable table = new JTable(data, columns){
            @Override
            public boolean isCellEditable(int row, int column) {
                if(tableAreaWorkMode == 0 || tableAreaWorkMode == 3){
                    return false;
                }else{
                    if(tableAreaWorkMode == 1){
                        if(tableShowOperateStatus){
                            return false;
                        }else {
                            return column != 0;
                        }
                    }
                    return true;
                }
            }
        };
        table.setBounds(0, 15, 570, 260);
        table.setFont(new Font("", Font.PLAIN, 11));
        JTableHeader header = table.getTableHeader();
        header.setReorderingAllowed(false);
        header.setBounds(0, 0, 570, 15);
        DefaultTableCellRenderer defaultTableCellRenderer = new DefaultTableCellRenderer();
        defaultTableCellRenderer.setHorizontalAlignment(JLabel.CENTER);
        defaultTableCellRenderer.setBackground(new Color(222,245,229));
        defaultTableCellRenderer.setFont(new Font("", Font.PLAIN, 10));
        header.setDefaultRenderer(defaultTableCellRenderer);
        // set the style of the table inner cells
        DefaultTableCellRenderer defaultTableCellRendererTableInner = new DefaultTableCellRenderer(){
            @Serial
            private static final long serialVersionUID = 1L;
            public Component getTableCellRendererComponent(JTable table,Object value, boolean isSelected,
                                                           boolean hasFocus, int row, int column){
                if(row % 2 == 0){
                    setBackground(new Color(255,236,239));
                }else {
                    setBackground(new Color(220,230,241));
                }
                if(tableAreaWorkMode == 1){
                    if(column == 0){
                        setBackground(new Color(234,234,234));
                        setForeground(new Color(178,178,178));
                    }else {
                        setForeground(new Color(0, 0, 0));
                    }
                    if(tableShowOperateStatus){
                        if(column == 7){
                            if(tableOperateStatus[row] == 0){
                                setBackground(new Color(91,245,99));
                                setForeground(new Color(68,127,53));
                            }else if(tableOperateStatus[row] == 1){
                                setBackground(new Color(215,107,107));
                                setForeground(new Color(155,5,6));
                            }else{
                                setBackground(new Color(178,178,178));
                                setForeground(new Color(67,68,61));
                            }
                        }
                    }
                }
                if(tableAreaWorkMode == 3){
                    String rowId = data[row][0];
                    for(String i: sysManager.this.deletedRow.toArray(new String[0])){
                        if(i.equals(rowId)){
                            setForeground(new Color(255, 5, 6));
                            break;
                        }else {
                            setForeground(new Color(0, 0, 0));
                        }
                    }
                }

                return super.getTableCellRendererComponent(table, value, isSelected, hasFocus, row, column);
            }
        };
        for(int i = 0; i < table.getColumnCount(); i += 1) {
            table.getColumn(table.getColumnName(i)).setCellRenderer(defaultTableCellRendererTableInner);
        }
        defaultTableCellRendererTableInner.setHorizontalAlignment(JLabel.CENTER);
        table.setDefaultRenderer(Object.class, defaultTableCellRendererTableInner);
        int[] tableColumnWidthConfig;
        if(this.tableShowOperateStatus){
            tableColumnWidthConfig = new int[]{18, 95, 175, 49, 49, 39, 85, 60};
        }else {
            tableColumnWidthConfig = new int[]{30, 100, 180, 56, 56, 48, 100};
        }

        TableColumnModel tableColumnModel = table.getColumnModel();
        for(int i = 0; i < tableColumnWidthConfig.length; i += 1){
            TableColumn tableColumn = tableColumnModel.getColumn(i);
            tableColumn.setPreferredWidth(tableColumnWidthConfig[i]);
            tableColumn.setMinWidth(tableColumnWidthConfig[i]);
            tableColumn.setMaxWidth(tableColumnWidthConfig[i]);
        }
        if(this.tableShowOperateStatus){
            this.tableAreaForegroundReminder.setText("<html><body><p>以下为方才欲新增的行及其插入情况，<span style='" +
                    "font-size: 1.3em; color: red; font-weight: bolder;'>单击选中列以查看错误信息</span></p></body></html>");
            table.addMouseListener(new MouseListener() {
                @Override
                public void mouseClicked(MouseEvent e) {
                    if(sysManager.this.errorReport != null){
                        sysManager.this.errorReport.setVisible(false);
                        sysManager.this.tableAreaForeground.remove(errorReport);
                        errorReport = null;
                    }
                    int rowIndex = table.getSelectedRow();
                    errorReport = new JLabel("所选行状态："+data[rowIndex][7]);
                    errorReport.setBounds(24, 323, 380, 20);
                    errorReport.setFont(new Font("", Font.PLAIN, 10));
                    if(sysManager.this.tableOperateStatus[rowIndex] == 0){
                        errorReport.setForeground(new Color(30,115,30));
                    } else if (sysManager.this.tableOperateStatus[rowIndex] == 1) {
                        errorReport.setForeground(new Color(255, 30, 30));
                    }else {
                        errorReport.setForeground(new Color(175,170,69));
                        if(data[rowIndex][7].equals("-")){
                            errorReport.setText("空行，未进行任何操作");
                        }
                    }
                    sysManager.this.tableAreaForeground.add(errorReport);
                    tableAreaForeground.repaint();
                }

                @Override
                public void mousePressed(MouseEvent e) {

                }

                @Override
                public void mouseReleased(MouseEvent e) {

                }

                @Override
                public void mouseEntered(MouseEvent e) {

                }

                @Override
                public void mouseExited(MouseEvent e) {

                }
            });
        }
        if(tableAreaWorkMode == 2){
            table.addMouseListener(new MouseListener() {
                @Override
                public void mouseClicked(MouseEvent e) {
                }

                @Override
                public void mousePressed(MouseEvent e) {
                }

                @Override
                public void mouseReleased(MouseEvent e) {
                    if(e.getButton() == 1){
                        listenValueChanged();
                    }
                }

                @Override
                public void mouseEntered(MouseEvent e) {
                }

                @Override
                public void mouseExited(MouseEvent e) {
                }
                private void listenValueChanged(){
                    // the first time click row
                    if(sysManager.this.lastChooseRowData == null){
                        sysManager.this.lastChooseRowIndex = table.getSelectedRow();
                        lastChooseRowData = new String[data[lastChooseRowIndex].length];
                        System.arraycopy(data[lastChooseRowIndex], 0,
                                lastChooseRowData, 0, data[lastChooseRowIndex].length);
                    }else {
                        int nowSelectedRow = table.getSelectedRow();
                        for(int i = 0; i < lastChooseRowData.length; i += 1){
                            if(!lastChooseRowData[i].equals(data[lastChooseRowIndex][i])){
                                sysManager.this.reviseRecordActuators(lastChooseRowData, data[lastChooseRowIndex], lastChooseRowIndex);
                            }
                        }
                        lastChooseRowIndex = nowSelectedRow;
                        lastChooseRowData = data[nowSelectedRow];
                        }
                }
            });
        }
        if(this.tableAreaWorkMode == 3){
            String[] finalColumns = columns;
            table.addMouseListener(new MouseListener() {
                @Override
                public void mouseClicked(MouseEvent e) {
                    if(e.getClickCount() == 2 && e.getButton() == 1){
                        int selectedRowIndex = table.getSelectedRow();
                        String[] deleteDestRow = data[selectedRowIndex];
                        sysManager.this.deleteRecordActuators(deleteDestRow, selectedRowIndex);


                        updateMainTable(data, finalColumns);
                    }
                }

                @Override
                public void mousePressed(MouseEvent e) {

                }

                @Override
                public void mouseReleased(MouseEvent e) {

                }

                @Override
                public void mouseEntered(MouseEvent e) {
                }

                @Override
                public void mouseExited(MouseEvent e) {

                }
            });
        }

        this.tableBar.add(header);
        this.tableBar.add(table, BorderLayout.SOUTH);
        this.tableBar.repaint();
    }
    private void setTableAreaWorkModeTo(int mode){
        this.tableShowOperateStatus = false;
        if(this.errorReport != null){
            this.tableAreaForeground.remove(this.errorReport);
            this.tableAreaForeground.repaint();
        }
        if(mode == 0 && this.tableAreaWorkMode != 0){
            this.tableAreaWorkMode = 0;
            this.nextPage.setText("下一页");
            this.previousPage.setText("上一页");
            this.pageCounterLabel.setVisible(true);
            this.nextPage.setEnabled(true);
            this.reviseRecord.setEnabled(true);
            this.deleteRecord.setEnabled(true);
        }
        if(mode == 1 && this.tableAreaWorkMode != 1){
            this.tableAreaWorkMode = 1;
            this.nextPage.setText("立即增加");
            this.previousPage.setText("清空");
            this.pageCounterLabel.setVisible(false);
            this.nextPage.setEnabled((true));
            this.deleteRecord.setEnabled(false);
            this.reviseRecord.setEnabled(false);
        }
        if(mode == 2 && this.tableAreaWorkMode != 2){
            this.tableAreaWorkMode = 2;
            this.previousPage.setVisible(true);
            this.pageCounterLabel.setVisible(true);
            this.nextPage.setEnabled(true);
        }
        if(mode == 3 && this.tableAreaWorkMode != 3){
            this.tableAreaWorkMode = 3;
            this.previousPage.setVisible(true);
            this.pageCounterLabel.setVisible(true);
            this.nextPage.setEnabled(true);

        }
    }
    private void createListener(){
        this.previousPage.addActionListener(e -> {
            if(tableAreaWorkMode == 0 || tableAreaWorkMode == 3 || tableAreaWorkMode == 2){
                if(this.tablePageCounter != 0){
                    String[][] shownTable = new String[this.tablePageRowNum][this.tableColumnNum];
                    this.tablePageCounter -= 1;
                    System.arraycopy(this.tableData, this.tablePageRowNum * (this.tablePageCounter) ,
                            shownTable, 0, this.tablePageRowNum);
                    this.updateMainTable(shownTable, this.tableHead);
                    this.pageCounterLabel.setText("第"+(this.tablePageCounter+1)+"/"+this.totalPageNum+"页");
                }
            }
            // clear table
            if(this.tableAreaWorkMode == 1){
                addRecordFunction();
            }
        });
        this.nextPage.addActionListener(e -> {
            if(this.tableAreaWorkMode == 0 || this.tableAreaWorkMode == 3 || tableAreaWorkMode == 2){
                if(totalPageNum-1 > tablePageCounter){
                    int thisRowNum = this.tablePageRowNum;
                    if(this.tablePageCounter == totalPageNum-2){
                        thisRowNum = this.tableData.length % this.tablePageRowNum;
                        if(thisRowNum == 0){
                            thisRowNum = this.tablePageRowNum;
                        }
                    }
                    String[][] shownTable = new String[thisRowNum][this.tableColumnNum];
                    this.tablePageCounter += 1;
                    System.arraycopy(this.tableData, this.tablePageCounter*this.tablePageRowNum,
                            shownTable, 0, thisRowNum);
                    this.updateMainTable(shownTable, this.tableHead);
                    this.pageCounterLabel.setText("第"+(this.tablePageCounter+1)+"/"+this.totalPageNum+"页");
                }
            }
            if(this.tableAreaWorkMode == 1){
                addRecordValueCheckAndSemaphoreDataGen();
            }
        });
        this.inquireById.addActionListener(e -> {
            setTableAreaWorkModeTo(0);
            String id = this.searchInfBox.getText();
            boolean showAll = false;
            if(id.equals("")){
                showAll = true;
                this.tableAreaForegroundReminder.setText("<html><body><p>没有输入id，为你展示<span style='color: red; font-size:1.2em;'>" +
                        "所有</span>信息：</p></body></html>");
            }
            this.tableAreaTopBarStatus.setText("<html><body><p style='color: red;'>查找信息</p></body></html>");
            if(!showAll){
                this.tableAreaForegroundReminder.setText("<html><body><p>以下是<span style='color: red; font-size:1.2em;'>" +
                        "id为'"+id+"'</span>的幼儿园的信息：</p></body></html>");
            }
            ArrayList<String[]> resDataList = new ArrayList<>();
                String[][] allData = this.getAllRowOfSchoolsInf();
                for(String[] row: allData){
                    if(row[0].equals(id) || showAll){
                        resDataList.add(row);
                    }
                }
            this.createTable(resDataList.toArray(new String[0][]), this.schoolsTableHead);
        });
        this.inquireByName.addActionListener(e -> {
            setTableAreaWorkModeTo(0);
            String name = this.searchInfBox.getText();
            boolean showAll = false;
            if(name.equals("")){
                showAll = true;
                this.tableAreaForegroundReminder.setText("<html><body><p>没有输入幼儿园名称，为你展示<span style='color: red; font-size:1.2em;'>" +
                        "所有</span>信息：</p></body></html>");
            }
            this.tableAreaTopBarStatus.setText("<html><body><p style='color: red;'>查找信息</p></body></html>");
            if(!showAll){
                this.tableAreaForegroundReminder.setText("<html><body><p>以下是<span style='color: red; font-size:1.2em;'>" +
                        "名称包含'"+name+"'</span>的幼儿园的信息：</p></body></html>");
            }
            ArrayList<String[]> resDataList = new ArrayList<>();
                String[][] allData = this.getAllRowOfSchoolsInf();
                for(String[] row: allData){
                    if(row[1].contains(name)){
                        resDataList.add(row);
                    }
                }
            this.createTable(resDataList.toArray(new String[0][]), this.schoolsTableHead);
        });
        this.inquireByAddress.addActionListener(e -> {
            setTableAreaWorkModeTo(0);
            String address = this.searchInfBox.getText();
            boolean showAll = false;
            if(address.equals("")){
                showAll = true;
                this.tableAreaForegroundReminder.setText("<html><body><p>没有输入幼儿园地址，为你展示<span style='color: red; font-size:1.2em;'>" +
                        "所有</span>信息：</p></body></html>");
            }
            this.tableAreaTopBarStatus.setText("<html><body><p style='color: red;'>查找信息</p></body></html>");
            if(!showAll){
                this.tableAreaForegroundReminder.setText("<html><body><p>以下是<span style='color: red; font-size:1.2em;'>" +
                        "幼儿园所在地包含'"+ address +"'</span>的幼儿园的信息：</p></body></html>");
            }
            ArrayList<String[]> resDataList = new ArrayList<>();
                String[][] allData = this.getAllRowOfSchoolsInf();
                for(String[] row: allData){
                    if(row[2].contains(address)){
                        resDataList.add(row);
                    }
                }
            this.createTable(resDataList.toArray(new String[0][]), this.schoolsTableHead);
        });
        this.inquireByDean.addActionListener(e -> {
            setTableAreaWorkModeTo(0);
            String deanName = this.searchInfBox.getText();
            boolean showAll = false;
            if(deanName.equals("")){
                showAll = true;
                this.tableAreaForegroundReminder.setText("<html><body><p>没有输入园长信息，为你展示<span style='color: red; font-size:1.2em;'>" +
                        "所有</span>信息：</p></body></html>");
            }
            this.tableAreaTopBarStatus.setText("<html><body><p style='color: red;'>查找信息</p></body></html>");
            if(!showAll){
                this.tableAreaForegroundReminder.setText("<html><body><p>以下是<span style='color: red; font-size:1.2em;'>" +
                        "园长为"+ deanName +"</span>的幼儿园的信息：</p></body></html>");
            }
            ArrayList<String[]> resDataList = new ArrayList<>();
                String[][] allData = this.getAllRowOfSchoolsInf();
                for(String[] row: allData){
                    if(row[5].equals(deanName) || showAll){
                        resDataList.add(row);
                    }
                }
            this.createTable(resDataList.toArray(new String[0][]), this.schoolsTableHead);
        });
        this.inquireByChildrenNumRange.addActionListener(e -> {
            setTableAreaWorkModeTo(0);
            String minChildrenText = this.rangeMinValue.getText();
            boolean doNotCheckMin = true;
            int minChildrenNum = 0;
            if(!minChildrenText.equals("")){
                doNotCheckMin = false;
                minChildrenNum = Integer.parseInt(minChildrenText);
            }
            String maxChildrenText = this.rangeMaxValue.getText();
            boolean doNotCheckMax = true;
            int maxChildrenNum = 0;
            if(!maxChildrenText.equals("")){
                doNotCheckMax = false;
                maxChildrenNum = Integer.parseInt(maxChildrenText);
            }
            this.tableAreaTopBarStatus.setText("<html><body><p style='color: red;'>查找信息</p></body></html>");
            if(!doNotCheckMin && !doNotCheckMax){
                this.tableAreaForegroundReminder.setText("<html><body><p>以下是<span style='color: red; font-size:1.2em;'>" +
                        "幼儿人数在"+minChildrenNum+"到"+maxChildrenNum+"之间</span>的幼儿园的信息：</p></body></html>");
            }else {
                if(!doNotCheckMin){
                    this.tableAreaForegroundReminder.setText("<html><body><p>以下是<span style='color: red; font-size:1.2em;'>" +
                            "幼儿人数大于"+minChildrenNum+"</span>的幼儿园的信息：</p></body></html>");
                }else {
                    if(!doNotCheckMax){
                        this.tableAreaForegroundReminder.setText("<html><body><p>以下是<span style='color: red; font-size:1.2em;'>" +
                                "幼儿人数小于"+maxChildrenNum+"</span>的幼儿园的信息：</p></body></html>");
                    }else {
                        this.tableAreaForegroundReminder.setText("<html><body><p>没有输入有效范围，以下是<span style='color: red; font-size:1.2em;'>" +
                                "全部的</span>的幼儿园的信息：</p></body></html>");
                    }
                }
            }
            ArrayList<String[]> resDataList = new ArrayList<>();
                String[][] allData = this.getAllRowOfSchoolsInf();
                for(String[] row: allData){
                    int thisRowChildrenNum = Integer.parseInt(row[3]);
                    if((doNotCheckMax&&!doNotCheckMin&&(thisRowChildrenNum >= minChildrenNum)) ||
                            (doNotCheckMin&&!doNotCheckMax&&(thisRowChildrenNum <= maxChildrenNum)) ||
                            (doNotCheckMin&&doNotCheckMax) ||
                            (!doNotCheckMin&&!doNotCheckMax&&(thisRowChildrenNum >= minChildrenNum && thisRowChildrenNum <= maxChildrenNum))){
                        resDataList.add(row);
                    }
                }
            this.createTable(resDataList.toArray(new String[0][]), this.schoolsTableHead);
        });
        this.inquireByEmployeeNumRange.addActionListener(e -> {
            setTableAreaWorkModeTo(0);
            String minEmployeeText = this.rangeMinValue.getText()+"";
            boolean doNotCheckMin = true;
            int minEmployeeNum = 1;
            if(!minEmployeeText.equals("")){
                doNotCheckMin = false;
                minEmployeeNum = Integer.parseInt(minEmployeeText);
            }
            String maxEmployeeText = this.rangeMaxValue.getText()+"";
            boolean doNotCheckMax = true;
            int maxEmployeeNum = 0;
            if(!maxEmployeeText.equals("")){
                doNotCheckMax = false;
                maxEmployeeNum = Integer.parseInt(maxEmployeeText);
            }
            this.tableAreaTopBarStatus.setText("<html><body><p style='color: red;'>查找信息</p></body></html>");
            if(!doNotCheckMin && !doNotCheckMax){
                this.tableAreaForegroundReminder.setText("<html><body><p>以下是<span style='color: red; font-size:1.2em;'>" +
                        "教职工人数在"+ minEmployeeNum +"到"+ maxEmployeeNum +"之间</span>的幼儿园的信息：</p></body></html>");
            }else {
                if(!doNotCheckMin){
                    this.tableAreaForegroundReminder.setText("<html><body><p>以下是<span style='color: red; font-size:1.2em;'>" +
                            "教职工人数大于"+ minEmployeeNum +"</span>的幼儿园的信息：</p></body></html>");
                }else {
                    if(!doNotCheckMax){
                        this.tableAreaForegroundReminder.setText("<html><body><p>以下是<span style='color: red; font-size:1.2em;'>" +
                                "教职工人数小于"+ maxEmployeeNum +"</span>的幼儿园的信息：</p></body></html>");
                    }else {
                        this.tableAreaForegroundReminder.setText("<html><body><p>没有输入有效范围，以下是<span style='color: red; font-size:1.2em;'>" +
                                "全部的</span>的幼儿园的信息：</p></body></html>");
                    }
                }
            }
            ArrayList<String[]> resDataList = new ArrayList<>();
                String[][] allData = this.getAllRowOfSchoolsInf();
                for(String[] row: allData){
                    int thisRowEmployeeNum = Integer.parseInt(row[4]);
                    if(!doNotCheckMin && !doNotCheckMax && thisRowEmployeeNum >= minEmployeeNum && thisRowEmployeeNum <= maxEmployeeNum ||
                            doNotCheckMax && doNotCheckMin ||
                            doNotCheckMin && thisRowEmployeeNum <= maxEmployeeNum ||
                            doNotCheckMax && thisRowEmployeeNum >= minEmployeeNum){
                        resDataList.add(row);
                    }
                }
            this.createTable(resDataList.toArray(new String[0][]), this.schoolsTableHead);
        });
        this.addRecord.addActionListener(e -> addRecordFunction());
        this.deleteRecord.addActionListener(e -> deleteRecordFunction());
        this.reviseRecord.addActionListener(e -> reviseRecordFunction());
    }
    private void createTable(String[][] tableData, String[] columns){
        this.tableData = tableData;
        this.tableHead = columns;
        this.tableColumnNum = columns.length;
        this.tablePageCounter = 0;
        this.totalPageNum = this.tableData.length/this.tablePageRowNum;
        if(this.tableData.length % this.tablePageRowNum != 0){
            totalPageNum += 1;
        }
        if(tableData.length > this.tablePageRowNum){
            String[][] shownTable = new String[this.tablePageRowNum][this.tableColumnNum];
            System.arraycopy(tableData, 0, shownTable, 0, this.tablePageRowNum);
            this.updateMainTable(shownTable, columns);
        }else {
            this.updateMainTable(tableData, columns);
        }
        this.pageCounterLabel.setText("第"+(this.tablePageCounter+1)+"/"+this.totalPageNum+"页");
    }
    private void addRecordFunction(){
        setTableAreaWorkModeTo(0);
        setTableAreaWorkModeTo(1);
        String[][] allSchoolsInf = this.getAllRowOfSchoolsInf();
        int idStartWith = Integer.parseInt(allSchoolsInf[allSchoolsInf.length-1][0]);
        this.tableAreaTopBarStatus.setText("增加新的记录");
        this.tableAreaForegroundReminder.setText("<html><body><p>双击下面的表格，填入要新增的记录，点击右下角的<span style='color: red; font-size: 1.2em; '>“立即增加”</span>按钮以确认</p></body></html>");
        String[][] data = new String[this.tablePageRowNum][this.tableColumnNum];
        for(int i = 0; i < this.tablePageRowNum; i += 1){
            data[i][0] = ""+(idStartWith+i+1);
        }
        createTable(data, schoolsTableHead);
    }
    private void addRecordValueCheckAndSemaphoreDataGen(){
        this.tableShowOperateStatus = true;
        String[] tableOperateStatusDetail = new String[this.tablePageRowNum];
        this.tableOperateStatus = new int[this.tablePageRowNum];
        boolean continueTryInsert = true;
        for(int i = 0; i < this.tablePageRowNum; i += 1){
            // check row all null
            if(!continueTryInsert){
                this.tableOperateStatus[i] = 2;
                tableOperateStatusDetail[i] = "前面行出错或为空，为保护ID连续性，其后方数据不准继续插入！";
                continue;
            }
            boolean thisRowIsEmpty = true;
            for(int j = 1; j < this.tableColumnNum; j += 1){
                if (this.tableData[i][j] != null && !this.tableData[i][j].equals("")) {
                    thisRowIsEmpty = false;
                    break;
                }
            }
            if(thisRowIsEmpty){
                this.tableOperateStatus[i] = 2;
                tableOperateStatusDetail[i] = "-";
                continueTryInsert = false;
                continue;
            }
            // check row error
            StringBuilder error = new StringBuilder();
            for(int j = 1; j < this.tableColumnNum; j += 1){
                if(this.tableData[i][j] == null){
                    error.append(this.schoolsTableHead[j]).append("值为null;");
                }
            }
            try{
                if(Integer.parseInt(this.tableData[i][3]) <= 0){
                    error.append("幼儿人数应大于0;");
                }
            }catch (Exception ex){
                error.append("幼儿人数应为数字;");
            }
            try{
                if(Integer.parseInt(this.tableData[i][4]) <= 0){
                    error.append("教职员人数需大于0;");
                }
            }catch (Exception ex){
                error.append("教职员人数应为数字;");
            }
            try{
                if(!this.tableData[i][6].matches("^1([3-9])[0-9]{9}$")){
                    error.append("电话号格式有误;");
                }
            }catch (Exception ignored){
                error.append("电话号格式有误;");
            }

            if(!error.toString().equals("")){
                this.tableOperateStatus[i] = 1;
                tableOperateStatusDetail[i] = error.toString();
                continueTryInsert = false;
                continue;
            }
            StringBuilder sql = new StringBuilder("insert into `schools`(`id`, `name`, `address`," +
                    " `numberOfChildren`, `numberOfEmployee`, `deanName`, `deanPhone`) values (");
            sql.append(this.tableData[i][0]).append(", ").append("'").append(this.tableData[i][1]).append("', ");
            sql.append("'").append(this.tableData[i][2]).append("', ").append(this.tableData[i][3]).append(", ");
            sql.append(this.tableData[i][4]).append(", ").append("'").append(this.tableData[i][5]).append("', ");
            sql.append("'").append(this.tableData[i][6]).append("')");
            boolean insertRes;
            try{
                insertRes = this.dataOperator.operateDbBySql(sql.toString());
            }catch (dataOperateException ex){
                ex.printStackTrace();
                insertRes = false;
            }
            if(!insertRes){
                this.tableOperateStatus[i] = 1;
                tableOperateStatusDetail[i] = "数据库错误";
                continueTryInsert = false;
            }else {
                this.tableOperateStatus[i] = 0;
                tableOperateStatusDetail[i] = "成功";
            }
        }
        String[][] withStateTable = new String[this.tableData.length][this.schoolsTableHead.length+1];
        for(int i = 0; i < this.tableData.length; i += 1){
            System.arraycopy(this.tableData[i], 0, withStateTable[i], 0, this.schoolsTableHead.length);
            withStateTable[i][this.schoolsTableHead.length] = tableOperateStatusDetail[i];
        }
        this.updateMainTable(withStateTable, this.schoolsTableHead);
        this.nextPage.setEnabled(false);
    }
    private void deleteRecordFunction(){
        this.deletedRow = new ArrayList<>();
        this.setTableAreaWorkModeTo(3);
        this.tableAreaTopBarStatus.setText("删除查找中的数据");
        this.tableAreaForegroundReminder.setText("<html><p>先在查找当中找到要删除的数据，点击左栏'删除记录'功能后，在表格中<span style='color: red; font-size: 1.3em; font-weight: bolder;'>左键双击数据行</span>即可删除</p>");
        this.createTable(this.tableData, this.schoolsTableHead);
    }
    private void deleteRecordActuators(String[] allTheValues, int selectedRowIndex){
        String sql = "delete from `schools` where " +
                "`id` = " + allTheValues[0] + " and " +
                "`name` = '" + allTheValues[1] + "' and " +
                "`address` = '" + allTheValues[2] + "' and " +
                "`numberOfChildren` = " + allTheValues[3] + " and " +
                "`numberOfEmployee` = " + allTheValues[4] + " and " +
                "`deanName` = '" + allTheValues[5] + "' and " +
                "`deanPhone` = '" + allTheValues[6] + "'";
        boolean operateState;
        try {
            operateState = this.dataOperator.operateDbBySql(sql);
            if(operateState){
                sysManager.this.deletedRow.add(allTheValues[0]);
            }
        }catch (dataOperateException e){
            operateState = false;
        }
        if(this.tableAreaWorkMode == 3){
            if(sysManager.this.errorReport != null){
                sysManager.this.tableAreaForeground.remove(sysManager.this.errorReport);
                sysManager.this.errorReport = null;
            }
            sysManager.this.errorReport = new JLabel();
            sysManager.this.errorReport.setBounds(24, 323, 380, 20);
            sysManager.this.errorReport.setFont(new Font("", Font.PLAIN, 10));
            if(operateState){
                errorReport.setText("所选行(红色字体标记，第"+(selectedRowIndex+1)+"行)已删除，刷新后将不可见");
                sysManager.this.errorReport.setForeground(new Color(25, 205, 25));
            }else {
                errorReport.setText("所选行(第"+(selectedRowIndex+1)+"行)删除失败了");
                sysManager.this.errorReport.setForeground(new Color(255, 25, 25));
            }
            sysManager.this.tableAreaForeground.add(sysManager.this.errorReport);
            sysManager.this.tableAreaForeground.repaint();
        }
    }
    private void reviseRecordFunction(){
        this.setTableAreaWorkModeTo(0);
        this.setTableAreaWorkModeTo(2);
        this.tableAreaTopBarStatus.setText("修改查找到的记录值");
        this.tableAreaForegroundReminder.setText("<html>在查询到需要修改的数据后，点击左侧栏'修改记录'进入本页面，<span style='font-size: 1.3em; font-weight: bolder; color: red;'>双击需要修改的单元格填入需要的值，单击其他行退出编辑即可保存修改</span></html>");
        this.createTable(this.tableData, this.schoolsTableHead);
    }
    private void reviseRecordActuators(String[] oldData, String[] newData, int changedRowIndex){

        StringBuilder errors = new StringBuilder();
        for(int i = 1; i < newData.length; i += 1){
            if(newData[i].equals("")){
                errors.append(this.schoolsTableHead[i]).append("不能为空;");
            }
        }
            try{
                int childrenNum = Integer.parseInt(newData[3]);
                if(childrenNum <= 0){
                    errors.append("幼儿人数应大于0；");
                }
            }catch (Exception ignored){
                errors.append("幼儿人数非数；");
            }
            try{
                int employeeNum = Integer.parseInt(newData[4]);
                if(employeeNum <= 0){
                    errors.append("教职员人数应大于0；");
                }
            }catch (Exception ignored){
                errors.append("教职员人数非数；");
            }
            try{
                if(!newData[6].matches("^1([3-9])[0-9]{9}$")){
                    errors.append("电话号有误；");
                }
            }catch (Exception ignored){
                errors.append("电话号有误");
            }
        if(!errors.toString().equals("")){
            for(int i = 0; i < this.tableData.length; i += 1){
                if(this.tableData[i][0].equals(newData[0])){
                    this.tableData[i] = oldData;
                    break;
                }
            }
            createTable(this.tableData, this.schoolsTableHead);
            this.errorReport = new JLabel();
            errorReport = new JLabel("修改记录失败："+ errors);
            errorReport.setBounds(24, 323, 380, 20);
            errorReport.setFont(new Font("", Font.PLAIN, 10));
            errorReport.setForeground(new Color(155, 0, 0));
            this.tableAreaForeground.add(errorReport);
            this.tableAreaForeground.repaint();
        }else {
            String sql = "update schools set `name`='"+newData[1]+"', `address`='"+newData[2]+"', `numberOfChildren`="+
                    newData[3]+", `numberOfEmployee`="+newData[4]+", `deanName`='"+newData[5]+"', `deanPhone`='"+newData[6]+
                    "' where `id`="+newData[0];
            boolean insertStatus;
            try{
                insertStatus = this.dataOperator.operateDbBySql(sql);
            }catch (dataOperateException e){
                insertStatus = false;
            }
            if(insertStatus){
                createTable(this.tableData, this.schoolsTableHead);
                this.errorReport = new JLabel();
                errorReport = new JLabel("第"+(changedRowIndex+1)+"行修改记录成功！");
                errorReport.setBounds(24, 323, 380, 20);
                errorReport.setFont(new Font("", Font.PLAIN, 10));
                errorReport.setForeground(new Color(0, 156, 0));
                this.tableAreaForeground.add(errorReport);
                this.tableAreaForeground.repaint();
            }else {
                for(int i = 0; i < this.tableData.length; i += 1){
                    if(this.tableData[i][0].equals(newData[0])){
                        this.tableData[i] = oldData;
                        break;
                    }
                }
                createTable(this.tableData, this.schoolsTableHead);
                this.errorReport = new JLabel();
                errorReport = new JLabel("修改记录失败：数据库错误！");
                errorReport.setBounds(24, 323, 380, 20);
                errorReport.setFont(new Font("", Font.PLAIN, 10));
                errorReport.setForeground(new Color(156, 0, 0));
                this.tableAreaForeground.add(errorReport);
                this.tableAreaForeground.repaint();
            }
        }
    }
    private String[][] getAllRowOfSchoolsInf(){
        String[][] allInf = null;
        try{
            allInf = this.dataOperator.inquireDataBySql("select * from `schools` order by `id`", "id", "name", "address", "numberOfChildren", "numberOfEmployee", "deanName", "deanPhone");
        }catch (dataOperateException e){
            e.printStackTrace();
        }
        assert allInf != null;
        return allInf;
    }
}

class demo{
    public static void main(String[] args) throws sysManagerException {
        new sysManager(new LoginUser("11111", "Developer", "admin", ""));
    }
}
