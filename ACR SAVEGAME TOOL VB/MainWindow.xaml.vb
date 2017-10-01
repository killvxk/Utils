Imports System.IO
Imports Microsoft.Win32

Class MainWindow

    Private Sub Button_Click_2(sender As Object, e As RoutedEventArgs)

        Dim openFileDialog1 As New OpenFileDialog()
        openFileDialog1.Title = "Choose your save"
        openFileDialog1.InitialDirectory = Directory.GetCurrentDirectory()
        openFileDialog1.Filter = "Save file (*.save)|*.save|All files (*.*)|*.*"
        openFileDialog1.FilterIndex = 1
        openFileDialog1.RestoreDirectory = True

        If openFileDialog1.ShowDialog() = True Then
            Try

                ' Insert code to read the stream here.
                'handle save file and check if it is 
                from1.Text = openFileDialog1.FileName



            Catch Ex As Exception
                MessageBox.Show("Cannot read file from disk. Original error: " & Ex.Message)
            Finally
                ' Check this again, since we need to make sure we didn't throw an exception on open.

            End Try
        End If
    End Sub



    Private Sub Button_Click_1(sender As Object, e As RoutedEventArgs)
        Dim saveFileDialog1 As New SaveFileDialog()

        saveFileDialog1.InitialDirectory = Directory.GetCurrentDirectory()
        saveFileDialog1.Filter = "Save file (*.save)|*.save|All files (*.*)|*.*"
        saveFileDialog1.FilterIndex = 1
        saveFileDialog1.RestoreDirectory = True

        If saveFileDialog1.ShowDialog() = True Then
            Try
                ' Insert code to read the stream here.
                'handle save file and check if it is 
                to1.Text = saveFileDialog1.FileName
            Catch Ex As Exception
                MessageBox.Show("Cannot read file from disk. Original error: " & Ex.Message)
            Finally
                ' Check this again, since we need to make sure we didn't throw an exception on open.

            End Try
        End If
    End Sub

    Function Failed()
        MsgBox("Failed")
        Return 1
    End Function

    Private Sub Button_Click_3(sender As Object, e As RoutedEventArgs)


        If (String.IsNullOrEmpty(from1.Text) = False) Or (String.IsNullOrEmpty(from1.Text) = False) Then

            Failed()

        End If
        'convert


        Dim key1d() As Byte = {0, 0}
        If (String.IsNullOrEmpty(key1.Text)) = True Then
            Failed()
        End If

        key1d = System.Text.Encoding.Default.GetBytes(key1.Text)


        Dim key2d() As Byte = {0, 0}

        If (String.IsNullOrEmpty(key2.Text)) = True Then
            Failed()
        End If

        key2d = System.Text.Encoding.Default.GetBytes(key2.Text)
        Dim origin = New FileStream(from1.Text, FileMode.Open, FileAccess.Read)
            'Dim saveok = New StreamWriter(to1.Text)


            Dim temp = New MemoryStream





            Select Case origin.ReadByte()


                Case &H04
                    origin.Seek(&H8, SeekOrigin.Begin)




                Case &H24
                    origin.Seek(&H28, SeekOrigin.Begin)

            End Select


            '头部
            temp.Seek(&H0, SeekOrigin.Begin)
            temp.WriteByte(&H04)
            temp.WriteByte(&H02)
            temp.WriteByte(&H00)
            temp.WriteByte(&H00)
            temp.WriteByte(&H00)
            temp.WriteByte(&H00)
            temp.WriteByte(&H00)
            temp.WriteByte(&H00)

            For i = &H8 To &H210
                temp.WriteByte(origin.ReadByte())
            Next i

            '解密
            origin.Seek(&H0, SeekOrigin.Begin)

            Select Case origin.ReadByte()


                Case &H04
                    origin.Seek(&H208, SeekOrigin.Begin)




                Case &H24
                    origin.Seek(&H228, SeekOrigin.Begin)

            End Select



            temp.Seek(&H208, SeekOrigin.Begin)


            Dim j = (origin.Length - origin.Position) Mod key1d.Length



            Dim a

            Do
                a = origin.ReadByte()

                If a = -1 Then Exit Do

                temp.WriteByte(a Xor key1d(j))

                j = j - 1

                If (j < 0) Then
                    j = UBound(key1d)

                End If


            Loop


            '加密
            Dim finish = New FileStream(to1.Text, FileMode.Create)
            temp.Seek(&H0, SeekOrigin.Begin)
            finish.Seek(&H0, SeekOrigin.Begin)

            For i = &H0 To &H210
                finish.WriteByte(temp.ReadByte())
            Next i

            temp.Seek(&H208, SeekOrigin.Begin)
            finish.Seek(&H208, SeekOrigin.Begin)

            j = (temp.Length - temp.Position) Mod key2d.Length

            Do
                a = temp.ReadByte()

                If a = -1 Then Exit Do

                finish.WriteByte(a Xor key2d(j))

                j = j - 1

                If (j < 0) Then
                    j = UBound(key2d)

                End If


            Loop


        temp.Close()
        origin.Close()
        finish.Close()



        MsgBox("ok")



    End Sub

End Class
