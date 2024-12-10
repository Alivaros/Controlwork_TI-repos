#pragma once
#include <queue>
#include <unordered_map>
#include <string>
#include <Windows.h>
#include <msclr/marshal_cppstd.h>
#include "HelpForm.h"
namespace TI7 {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::Text::RegularExpressions;
    using namespace std;

    struct Node {
        char ch;
        int freq;
        Node* left, * right;


        // конструктор узла
        Node(char ch, int freq, Node* left = nullptr, Node* right = nullptr)
        {
            this->ch = ch;
            this->freq = freq;
            this->left = left;
            this->right = right;
        }
    };
    // структура для сравнения узлов в приор. очереди
    struct compare
    {
        bool operator()(Node* left, Node* right) {
            return left->freq > right->freq;
        }
    };
    // Этап 1: подсчет частот символов( по принципу сколько раз встречается в тексте)
    void calcFreq(const string& text, unordered_map<char, int>& freq)
    {
        for (char ch : text)
        {
            freq[ch]++;
        }
    }
    // Этапы 2-5: построение дерева Хаффмана
    Node* buildHuffmanTree(unordered_map<char, int>& freq) {
        priority_queue<Node*, vector<Node*>, compare> minHeap;
        // Заполняем приоритетную очередь узлами (этап 2)
        for (const auto& pair : freq) {
            minHeap.push(new Node(pair.first, pair.second));
        }
        // Построение дерева Хаффмана (3-5)
        while (minHeap.size() > 1) {
            Node* left = minHeap.top();
            minHeap.pop();

            Node* right = minHeap.top();
            minHeap.pop();

            int sum = left->freq + right->freq;
            minHeap.push(new Node('\0', sum, left, right));
        }

        if (!minHeap.empty()) {
            return minHeap.top();
        }
        else {
            return nullptr;
        }
    }
    // Этап 6: генерация кодов Хаффмана
    void gencode(Node* root, string str, unordered_map<char, string>& huffmanCode) {
        if (root == nullptr) {
            return;
        }

        if (root->ch != '\0') {
            huffmanCode[root->ch] = str;
        }

        gencode(root->left, str + "0", huffmanCode);
        gencode(root->right, str + "1", huffmanCode);
    }

    /// <summary>
    /// Сводка для MyForm
    /// </summary>
    public ref class MyForm : public System::Windows::Forms::Form
    {
    public:
        MyForm(void)
        {
            InitializeComponent();
            //
            //TODO: добавьте код конструктора
            //
        }

    protected:
        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        ~MyForm()
        {
            if (components)
            {
                delete components;
            }
        }
    private: System::Windows::Forms::TextBox^ textBoxInput;
    private: System::Windows::Forms::TextBox^ textBoxOutput;
    protected:

    protected:



    private: System::Windows::Forms::Button^ buttonCalc;
    private: System::Windows::Forms::Button^ buttonHelp;
    private: System::Windows::Forms::Button^ buttonClose;
    private: System::Windows::Forms::Label^ label1;
    private: System::Windows::Forms::Label^ label2;
    private: System::Windows::Forms::DataGridView^ dataGridView;

    private: System::Windows::Forms::Label^ label3;





    private: System::Windows::Forms::GroupBox^ groupBox1;



    private: System::Windows::Forms::Button^ buttonClear;



    private: System::Windows::Forms::Label^ label4;
    private: System::Windows::Forms::TextBox^ textBoxLenCode;
    private: System::Windows::Forms::DataGridViewTextBoxColumn^ Symbol;
    private: System::Windows::Forms::DataGridViewTextBoxColumn^ Freq;
    private: System::Windows::Forms::DataGridViewTextBoxColumn^ Code;
    private: System::Windows::Forms::DataGridViewTextBoxColumn^ Len;



















    private:
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        System::ComponentModel::Container^ components;


#pragma region Windows Form Designer generated code
        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        void InitializeComponent(void)
        {
            this->textBoxInput = (gcnew System::Windows::Forms::TextBox());
            this->textBoxOutput = (gcnew System::Windows::Forms::TextBox());
            this->buttonCalc = (gcnew System::Windows::Forms::Button());
            this->buttonHelp = (gcnew System::Windows::Forms::Button());
            this->buttonClose = (gcnew System::Windows::Forms::Button());
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->label2 = (gcnew System::Windows::Forms::Label());
            this->dataGridView = (gcnew System::Windows::Forms::DataGridView());
            this->Symbol = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->Freq = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->Code = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->Len = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->label3 = (gcnew System::Windows::Forms::Label());
            this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
            this->buttonClear = (gcnew System::Windows::Forms::Button());
            this->label4 = (gcnew System::Windows::Forms::Label());
            this->textBoxLenCode = (gcnew System::Windows::Forms::TextBox());
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView))->BeginInit();
            this->groupBox1->SuspendLayout();
            this->SuspendLayout();
            // 
            // textBoxInput
            // 
            this->textBoxInput->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->textBoxInput->Location = System::Drawing::Point(16, 44);
            this->textBoxInput->Multiline = true;
            this->textBoxInput->Name = L"textBoxInput";
            this->textBoxInput->Size = System::Drawing::Size(452, 30);
            this->textBoxInput->TabIndex = 0;
            this->textBoxInput->TextChanged += gcnew System::EventHandler(this, &MyForm::textBoxInput_TextChanged);
            // 
            // textBoxOutput
            // 
            this->textBoxOutput->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->textBoxOutput->Location = System::Drawing::Point(16, 365);
            this->textBoxOutput->Multiline = true;
            this->textBoxOutput->Name = L"textBoxOutput";
            this->textBoxOutput->ReadOnly = true;
            this->textBoxOutput->Size = System::Drawing::Size(446, 30);
            this->textBoxOutput->TabIndex = 1;
            // 
            // buttonCalc
            // 
            this->buttonCalc->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->buttonCalc->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->buttonCalc->Location = System::Drawing::Point(10, 21);
            this->buttonCalc->Name = L"buttonCalc";
            this->buttonCalc->Size = System::Drawing::Size(143, 37);
            this->buttonCalc->TabIndex = 3;
            this->buttonCalc->Text = L"Выполнить";
            this->buttonCalc->UseVisualStyleBackColor = true;
            this->buttonCalc->Click += gcnew System::EventHandler(this, &MyForm::buttonCalc_Click);
            // 
            // buttonHelp
            // 
            this->buttonHelp->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->buttonHelp->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->buttonHelp->Location = System::Drawing::Point(308, 21);
            this->buttonHelp->Name = L"buttonHelp";
            this->buttonHelp->Size = System::Drawing::Size(143, 37);
            this->buttonHelp->TabIndex = 4;
            this->buttonHelp->Text = L"Справка";
            this->buttonHelp->UseVisualStyleBackColor = true;
            this->buttonHelp->Click += gcnew System::EventHandler(this, &MyForm::buttonHelp_Click);
            // 
            // buttonClose
            // 
            this->buttonClose->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->buttonClose->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->buttonClose->Location = System::Drawing::Point(10, 64);
            this->buttonClose->Name = L"buttonClose";
            this->buttonClose->Size = System::Drawing::Size(441, 37);
            this->buttonClose->TabIndex = 5;
            this->buttonClose->Text = L"Выход";
            this->buttonClose->UseVisualStyleBackColor = true;
            this->buttonClose->Click += gcnew System::EventHandler(this, &MyForm::buttonClose_Click);
            // 
            // label1
            // 
            this->label1->AutoSize = true;
            this->label1->BackColor = System::Drawing::SystemColors::Control;
            this->label1->Font = (gcnew System::Drawing::Font(L"Times New Roman", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label1->Location = System::Drawing::Point(139, 18);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(219, 23);
            this->label1->TabIndex = 6;
            this->label1->Text = L"Кодируемое сообщение";
            // 
            // label2
            // 
            this->label2->AutoSize = true;
            this->label2->BackColor = System::Drawing::SystemColors::Control;
            this->label2->Font = (gcnew System::Drawing::Font(L"Times New Roman", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label2->Location = System::Drawing::Point(139, 79);
            this->label2->Name = L"label2";
            this->label2->Size = System::Drawing::Size(203, 23);
            this->label2->TabIndex = 7;
            this->label2->Text = L"Таблица Кодирования";
            // 
            // dataGridView
            // 
            this->dataGridView->AllowUserToAddRows = false;
            this->dataGridView->AllowUserToDeleteRows = false;
            this->dataGridView->AllowUserToResizeColumns = false;
            this->dataGridView->AllowUserToResizeRows = false;
            this->dataGridView->BackgroundColor = System::Drawing::SystemColors::Control;
            this->dataGridView->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
            this->dataGridView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(4) {
                this->Symbol,
                    this->Freq, this->Code, this->Len
            });
            this->dataGridView->Location = System::Drawing::Point(16, 105);
            this->dataGridView->Name = L"dataGridView";
            this->dataGridView->ReadOnly = true;
            this->dataGridView->RowHeadersVisible = false;
            this->dataGridView->RowHeadersWidth = 51;
            this->dataGridView->Size = System::Drawing::Size(452, 214);
            this->dataGridView->TabIndex = 8;
            this->dataGridView->TabStop = false;
            // 
            // Symbol
            // 
            this->Symbol->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
            this->Symbol->HeaderText = L"Входной Символ";
            this->Symbol->MinimumWidth = 6;
            this->Symbol->Name = L"Symbol";
            this->Symbol->ReadOnly = true;
            this->Symbol->Resizable = System::Windows::Forms::DataGridViewTriState::False;
            // 
            // Freq
            // 
            this->Freq->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
            this->Freq->HeaderText = L"Вероятность";
            this->Freq->MinimumWidth = 6;
            this->Freq->Name = L"Freq";
            this->Freq->ReadOnly = true;
            this->Freq->Resizable = System::Windows::Forms::DataGridViewTriState::False;
            // 
            // Code
            // 
            this->Code->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
            this->Code->HeaderText = L"Код";
            this->Code->MinimumWidth = 6;
            this->Code->Name = L"Code";
            this->Code->ReadOnly = true;
            this->Code->Resizable = System::Windows::Forms::DataGridViewTriState::False;
            // 
            // Len
            // 
            this->Len->HeaderText = L"Длина";
            this->Len->MinimumWidth = 6;
            this->Len->Name = L"Len";
            this->Len->ReadOnly = true;
            this->Len->Width = 125;
            // 
            // label3
            // 
            this->label3->AutoSize = true;
            this->label3->BackColor = System::Drawing::SystemColors::Control;
            this->label3->Font = (gcnew System::Drawing::Font(L"Times New Roman", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label3->Location = System::Drawing::Point(22, 339);
            this->label3->Name = L"label3";
            this->label3->Size = System::Drawing::Size(427, 23);
            this->label3->TabIndex = 9;
            this->label3->Text = L"Закодированная последовательность символов";
            // 
            // groupBox1
            // 
            this->groupBox1->BackColor = System::Drawing::SystemColors::Control;
            this->groupBox1->Controls->Add(this->buttonHelp);
            this->groupBox1->Controls->Add(this->buttonClear);
            this->groupBox1->Controls->Add(this->buttonClose);
            this->groupBox1->Controls->Add(this->buttonCalc);
            this->groupBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->groupBox1->Location = System::Drawing::Point(12, 444);
            this->groupBox1->Name = L"groupBox1";
            this->groupBox1->Size = System::Drawing::Size(461, 107);
            this->groupBox1->TabIndex = 11;
            this->groupBox1->TabStop = false;
            this->groupBox1->Text = L"Панель управления";
            // 
            // buttonClear
            // 
            this->buttonClear->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->buttonClear->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->buttonClear->Location = System::Drawing::Point(159, 21);
            this->buttonClear->Name = L"buttonClear";
            this->buttonClear->Size = System::Drawing::Size(143, 37);
            this->buttonClear->TabIndex = 10;
            this->buttonClear->Text = L"Очистить";
            this->buttonClear->UseVisualStyleBackColor = true;
            this->buttonClear->Click += gcnew System::EventHandler(this, &MyForm::buttonClear_Click);
            // 
            // label4
            // 
            this->label4->AutoSize = true;
            this->label4->BackColor = System::Drawing::SystemColors::Control;
            this->label4->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label4->Location = System::Drawing::Point(12, 409);
            this->label4->Name = L"label4";
            this->label4->Size = System::Drawing::Size(234, 21);
            this->label4->TabIndex = 12;
            this->label4->Text = L"Длина кодовой комбинации";
            // 
            // textBoxLenCode
            // 
            this->textBoxLenCode->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->textBoxLenCode->Location = System::Drawing::Point(252, 409);
            this->textBoxLenCode->Name = L"textBoxLenCode";
            this->textBoxLenCode->ReadOnly = true;
            this->textBoxLenCode->Size = System::Drawing::Size(100, 29);
            this->textBoxLenCode->TabIndex = 13;
            this->textBoxLenCode->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
            // 
            // MyForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->BackColor = System::Drawing::Color::LightSteelBlue;
            this->ClientSize = System::Drawing::Size(485, 563);
            this->ControlBox = false;
            this->Controls->Add(this->textBoxLenCode);
            this->Controls->Add(this->label4);
            this->Controls->Add(this->groupBox1);
            this->Controls->Add(this->label3);
            this->Controls->Add(this->dataGridView);
            this->Controls->Add(this->label2);
            this->Controls->Add(this->label1);
            this->Controls->Add(this->textBoxOutput);
            this->Controls->Add(this->textBoxInput);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->MaximizeBox = false;
            this->MinimizeBox = false;
            this->Name = L"MyForm";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->Text = L"Эффективное кодирование. Метод Хаффмана";
            this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView))->EndInit();
            this->groupBox1->ResumeLayout(false);
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion
        System::Void checkfields()
        {
            Regex^ regex = gcnew Regex("^.{2,}$");
            this->buttonCalc->Enabled =
                regex->IsMatch(this->textBoxInput->Text);
        }
        // Функция простой сортировки (Bubble Sort)
        void simpleSort(vector<pair<char, int>>& vec) {
            bool swapped;
            do {
                swapped = false;
                for (size_t i = 0; i < vec.size() - 1; ++i) {
                    if (vec[i].second > vec[i + 1].second) {
                        swap(vec[i], vec[i + 1]);
                        swapped = true;
                    }
                }
            } while (swapped);
        }

        void Convert(String^ input, TextBox^ output, DataGridView^ dataGridView) {
            // Конвертируем входной текст в std::string
            string text = msclr::interop::marshal_as<string>(input);

            // Создаем частотный словарь
            unordered_map<char, int> freq;
            calcFreq(text, freq);

            // Преобразуем частотный словарь в вектор для сортировки
            vector<pair<char, int>> freqVec(freq.begin(), freq.end());

            // Сортируем вектор по частоте появления
            simpleSort(freqVec);

            // Строим дерево Хаффмана
            Node* root = buildHuffmanTree(freq);

            // Генерируем коды Хаффмана
            unordered_map<char, string> huffmanCode;
            gencode(root, "", huffmanCode);

            // Кодируем исходный текст
            string encodedText;
            for (char ch : text) {
                encodedText += huffmanCode[ch];
                encodedText += " ";
            }

            // Отображаем результат в TextBox
            output->Text = gcnew String(encodedText.c_str());

            fillDataGridView(dataGridView, huffmanCode, freq);
        }

        void fillDataGridView(DataGridView^ dGV, const std::unordered_map<char, std::string>& huffmanCode, const unordered_map<char, int>& freq)
        {
            dGV->Rows->Clear();
            for (const auto& kvalue : freq) {
                int rowIndex = dGV->Rows->Add();
                dGV->Rows[rowIndex]->Cells["Symbol"]->Value = gcnew String(std::string(1, kvalue.first).c_str());
                dGV->Rows[rowIndex]->Cells["Code"]->Value = gcnew String(huffmanCode.at(kvalue.first).c_str());
                dGV->Rows[rowIndex]->Cells["Freq"]->Value = (float(kvalue.second) / float(textBoxInput->TextLength));
                dGV->Rows[rowIndex]->Cells["Len"]->Value = gcnew String(huffmanCode.at(kvalue.first).length().ToString());

            }

        }
    private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
        buttonCalc->Enabled = false;
    }
    private: System::Void buttonClose_Click(System::Object^ sender, System::EventArgs^ e) {
        this->Close();
    }
    private: System::Void buttonCalc_Click(System::Object^ sender, System::EventArgs^ e) {
        Convert(textBoxInput->Text, textBoxOutput, dataGridView);
        textBoxLenCode->Text = textBoxOutput->Text->Length.ToString();
    }
    private: System::Void buttonClear_Click(System::Object^ sender, System::EventArgs^ e) {
        textBoxInput->Clear();
        textBoxOutput->Clear();
        textBoxLenCode->Clear();
        this->dataGridView->Rows->Clear();


    }
    private: System::Void textBoxInput_TextChanged(System::Object^ sender, System::EventArgs^ e) {
        checkfields();
    }
    private: System::Void buttonHelp_Click(System::Object^ sender, System::EventArgs^ e) {
        System::Windows::Forms::DialogResult dr;
        HelpForm^ newDlg = gcnew HelpForm();
    helpm:
        dr = newDlg->ShowDialog();
        if (dr == System::Windows::Forms::DialogResult::OK)
            return;
        else {
            MessageBox::Show("Ошибка закрытия справки");
            goto helpm;
        }

    }
    };
}
