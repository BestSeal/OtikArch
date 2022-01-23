using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Security.Cryptography;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using Lab3.DataObjects;
using Lab3.UnmanagedCode;
using Microsoft.Win32;
using Ookii.Dialogs.Wpf;

namespace Lab3
{
    public partial class MainWindow : Window
    {
        private List<string> _filePaths = new();

        private ArchInfo _archInfo;

        public MainWindow()
        {
            InitializeComponent();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            var openFileDialog = new OpenFileDialog
            {
                Multiselect = true,
                CheckFileExists = true
            };

            if (openFileDialog.ShowDialog() == true)
            {
                var filePaths = openFileDialog.FileNames;
                if (filePaths.Length <= 0) return;

                var gridView = new GridView();
                SelectedFiles.View = new GridView();

                gridView.Columns.Add(new GridViewColumn()
                {
                    Header = "Files to archive:",
                    DisplayMemberBinding = new Binding(nameof(FileView.FileName))
                });

                foreach (var filePath in filePaths)
                {
                    if (!string.IsNullOrEmpty(filePath) && File.Exists(filePath))
                    {
                        _filePaths.Add(filePath);

                        // var fileInfo = new FileInfo(filePath);
                        // var icon = System.Drawing.Icon.ExtractAssociatedIcon(filePath);
                        // var item = new ListViewItem();
                        // var panel = new StackPanel();
                        // var image = new Image();
                        // if (icon != null)
                        // {
                        //     var img = icon.ToBitmap();
                        //     var imgSource = new ImageSourceConverter();
                        //     image.Source = new BitmapImage();
                        // }
                        // panel.Children.Add(new TextBlock()
                        // {
                        //     Text = fileInfo.Name
                        // });
                        // SelectedFiles.Items.Add(panel);
                    }
                }

                ArchName.Text = Path.GetFileName(_filePaths.FirstOrDefault() ?? "OtikArch");
            }
        }


        private void MakeArchiveOnClick(object sender, RoutedEventArgs e)
        {
            if (_filePaths?.Count > 0 && !string.IsNullOrEmpty(SavePath.Text) && !string.IsNullOrEmpty(ArchName.Text))
            {
                _archInfo = new ArchInfo(ArchName.Text, _filePaths, SavePath.Text);
                var status = OtikArchNative.MakeArch(_archInfo.ArchName,
                    _archInfo.ArchName.Length,
                    _archInfo.FilePaths,
                    _archInfo.FilePaths.Length,
                    _archInfo.OutFilaPath,
                    _archInfo.OutFilaPath.Length,
                    false,
                    false,
                    false);
            }
        }

        private void ChooseSavePathOnClick(object sender, RoutedEventArgs e)
        {
            var openFileDialog = new VistaFolderBrowserDialog();

            if (openFileDialog.ShowDialog() == true)
            {
                var path = openFileDialog.SelectedPath;
                SavePath.Text = path;
            }
        }
    }
}