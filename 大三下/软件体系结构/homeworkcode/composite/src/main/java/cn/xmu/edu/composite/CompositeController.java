package cn.xmu.edu.composite;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextInputDialog;
import javafx.stage.DirectoryChooser;
import javafx.stage.Stage;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Optional;

public class CompositeController {

    @FXML
    public TextArea textArea;
    @FXML
    public Label label;
    private Stage stage;
    private String currentFolderPath;
    private Directory root;

    @FXML
    public void initialize() {
        label.setText("Please select a directory to begin");
    }
    @FXML
    public void selectButtonClick(ActionEvent actionEvent) {
        DirectoryChooser directoryChooser = new DirectoryChooser();
        directoryChooser.setTitle("Select Directory");
        File selectedDirectory = directoryChooser.showDialog(stage);

        if (selectedDirectory != null) {
            currentFolderPath = selectedDirectory.getAbsolutePath();
            label.setText("Current Directory: " + currentFolderPath);
            root = new Directory(selectedDirectory.getName());

            buildTree(selectedDirectory, root);

            textArea.clear();
            textArea.setText(root.printList());
        }
    }

    private void buildTree(File file, Directory directory) {
        File[] files = file.listFiles();
        if (files != null) {
            for (File f : files) {
                if (f.isDirectory()) {
                    Directory subDirectory = new Directory(f.getName());
                    directory.add(subDirectory);
                    buildTree(f, subDirectory);
                } else {
                    directory.add(new cn.xmu.edu.composite.File(f.getName(), (int) f.length()));
                }
            }
        }
    }

    @FXML
    public void onCreateFileButtonClick(ActionEvent actionEvent) {
        if (currentFolderPath.isEmpty()) {
            label.setText("Please select a directory first");
            return;
        }
        TextInputDialog fileNameDialog = new TextInputDialog();
        fileNameDialog.setTitle("Create File");
        fileNameDialog.setHeaderText("Enter file name");
        Optional<String> fileNameResult = fileNameDialog.showAndWait();

        if (fileNameResult.isPresent()) {
            String fileName = fileNameResult.get();
            File newFile = new File(currentFolderPath, fileName);

            if (newFile.exists()) {
                label.setText("File already exists");
                return;
            }

            try (FileWriter fileWriter = new FileWriter(newFile)) {
                fileWriter.write("");
                fileWriter.flush();
                int fileSize = 0;

                // Find the current folder in the composite tree and add the new file
                Entry currentFolder = findFolder(root, new File(currentFolderPath).getName());
                if (currentFolder instanceof Directory) {
                    ((Directory) currentFolder).add(new cn.xmu.edu.composite.File(fileName, fileSize));
                } else {
                    label.setText("Could not find the current folder");
                    return;
                }

                textArea.clear();
                textArea.setText(root.printList());
            } catch (IOException e) {
                e.printStackTrace();
            }
        } else {
            label.setText("File name cannot be empty");
        }
    }

    private Entry findFolder(Entry entry, String folderName) {
        if (entry instanceof Directory directory) {
            if (directory.getName().equals(folderName)) {
                return directory;
            } else {
                for (Object item : directory.getDirectory()) {
                    if (item instanceof Entry) {
                        Entry found = findFolder((Entry) item, folderName);
                        if (found != null) {
                            return found;
                        }
                    }
                }
            }
        }
        return null;
    }

    @FXML
    public void onCreateFoldButtonClick(ActionEvent actionEvent) {
        String currentFolderPath = label.getText().replace("Current Directory: ", "");
        if (currentFolderPath.isEmpty()) {
            label.setText("Please select a directory first");
            return;
        }

        TextInputDialog folderNameDialog = new TextInputDialog();
        folderNameDialog.setTitle("Create Folder");
        folderNameDialog.setHeaderText("Enter folder name");
        Optional<String> folderNameResult = folderNameDialog.showAndWait();

        if (folderNameResult.isPresent()) {
            String folderName = folderNameResult.get();
            File newFolder = new File(currentFolderPath, folderName);

            if (!newFolder.exists()) {
                if (newFolder.mkdir()) {
                    Directory newDirectory = new Directory(folderName);

                    Entry currentFolder = findFolder(root, new File(currentFolderPath).getName());
                    if (currentFolder instanceof Directory) {
                        ((Directory) currentFolder).add(newDirectory);
                    } else {
                        label.setText("Could not find the current folder");
                        return;
                    }

                    textArea.clear();
                    textArea.setText(root.printList());
                } else {
                    label.setText("Failed to create folder");
                }
            } else {
                label.setText("Folder already exists");
            }
        } else {
            label.setText("Folder name cannot be empty");
        }
    }
}
